#include "Base.h"
#include "InputParsers/FileParser.h"
#include "Analyzers/ClubAnalyzer.h"
#include "Club.h"
#include "Subscribers/Subscriber.h"
#include "EventDistributor.h"


#include "Events/InEventBody.h"
#include "Events/InEventBodyUser.h"
#include "Events/InEventBodyUserTable.h"
#include "Events/OutEventBodyError.h"
#include "Events/OutEventBodyUser.h"
#include "Events/OutEventBodyUserTable.h"



int main()
{
	/* event queue */
	std::queue<Event> event_q;

	/* declare open/close events */
	InEventBody ev0("0"); // close club
	InEventBody ev100("100"); // open club


	FileParser fpars("log2.txt");
	ClubAnalyzer analyzer(fpars,ev100,ev0);

	/* base club configs */
	uint32_t tables_amount = 0;
	uint32_t start_time = 0, end_time = 0;
	uint32_t price = 0;

	/* get club configs */
	analyzer.get_config(tables_amount, start_time, end_time, price);

	/* declare events */
	InEventBodyUser ev1("1"); // client came
	InEventBodyUser ev3("3"); // client waiting
	InEventBodyUser ev4("4"); // client left
	InEventBodyUserTable ev2("2", tables_amount); // client sat

	OutEventBodyUser ev11("11"); // client left (outcoming)
	OutEventBodyUserTable ev12("12"); //client sat (from Queue)
	OutEventBodyError ev13("13"); // error event


	/* analyze input data */
	if (!analyzer.analyze())
		return 1;

	/* get analyzed Event queue */
	event_q = analyzer.get_event_queue();

	/* init incoming events dispatcher */
	EventDistributor event_player(event_q);

	/* init club */
	Club club(tables_amount, start_time, end_time, price);


	/* subscribe to events */
	event_player.add_sub(ev0, &club, &Club::close_club_handler);
	event_player.add_sub(ev100, &club, &Club::open_club_handler);

	event_player.add_sub(ev1, &club, &Club::client_came_handler);
	event_player.add_sub(ev2, &club, &Club::client_sat_handler);
	event_player.add_sub(ev3, &club, &Club::client_waiting_handler);
	event_player.add_sub(ev4, &club, &Club::client_left_handler);
	
	club.add_sub(ev11, &club, &Club::client_must_leave_handler);
	club.add_sub(ev12, &club, &Club::client_must_sit_down_handler);
	club.add_sub(ev13, &club, &Club::error_handler);

	
	event_player.call_events();



	return 0;
}