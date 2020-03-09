#ifndef TEST_H_INCLUDED__
#define TEST_H_INCLUDED__

#define BANNER \
    "\n\nEECE202 BOARD TEST PROGRAM\n" \
    "by Jesus Calvino-Fraga, Version 1.2, Jan/2012\n" \
    "\nType `help` for help\n" \

#define HELP \
	"\nAvailable commands:\n\n" \
	"Lcd1, Lcd2:   Write to either line 1 or line 2 of LCD.\n" \
	"Help, ?:      This Help.\n" \
	"Clear, Cls:   Clear screen.\n" \
	"Adc:          Displays the voltages attached to the MCP3008 converter.\n" \
	"V:            8-input voltmeter! (LCD display required)\n" \
	"Map:          Draws an Ascii world map.\n" \
	"Count:        Display the counter tied to RTI.\n" \

#define WORLDMAP "\n\n" \
	":::::::::::``  ``::`      `::::::  `:::::::::::::`.:::::::::::::::\n" \
	":::::::::` :. :  :         ::::::  :::::::::::.:::`:::::::::::::::\n" \
	"::::::::::  :   :::.       :::::::::::::..::::`     :::: : :::::::\n" \
	"::::::::    :`:   ::`     ` ::::::::::::: :`           `` `:::::::\n" \
	":`        : `   :  ::    .::::::::`    `                        .:\n" \
	":               :  .:: .::. ::::`                              :::\n" \
	":. .,.        :::  `:::::::::::.: `                      .:...::::\n" \
	":::::::.      `     .::::::: ```                         :: :::::.\n" \
	"::::::::            `:::::::::  ``,            `    `   .:::::::::\n" \
	"::::::::.        :::::::::::: ``:,:   `    :         ``` :::::::::\n" \
	"::::::::::      ::::::::::::`                        :::::::::::::\n" \
	": .::::::::.   .:``::::::::    `         ::   :   `::.::::::::::::\n" \
	":::::::::::::::. `  `::::::.  `  `     :::::.:.:.:.:.:::::::::::::\n" \
	":::::::::::::::: :     `:::::::::   ` ,:::::::::: : :.:`::::::::::\n" \
	"::::::::::::::::: `     :::::::::   . :`::::::::::::::` `:::::::::\n" \
	"::::::::::::::::::``   :::::::::: :` : ,:::::::::::`      `:::::::\n" \
	":::::::::::::::::`   .::::::::::::  ::::::::::::::::       :::::::\n" \
	":::::::::::::::::. .::::::::::::::::::::::::::::::::::::.`::::::::\n" \
	":::::::::::::::::` :::::::::::::::::::::::::::::::::::::::::::::::\n" \
	"::::::::::::::::::.:::::::::::::::::::::::::::::::::::::::::::::::\n"

#endif	// TEST_H_INCLUDED__