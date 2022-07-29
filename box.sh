#!/bin/bash

for i in 148 149
do
    x=$(printf '\\x%x' "$i")
    printf "e2 %x --:\n" "$i"
    for j in {0..3}
    do
        printf "  "
        for k in {0..15}
        do
            n=$(expr $j \* 16 + $k + 128)
            printf "%x \xe2$x%b  " "$n" $(printf '\\x%x' "$n")
        done
        printf "\n"
    done
done

# https://www.utf8-chartable.de/unicode-utf8-table.pl?start=9472

# U+2500	─	e2 94 80	BOX DRAWINGS LIGHT HORIZONTAL
# U+2501	━	e2 94 81	BOX DRAWINGS HEAVY HORIZONTAL
# U+2502	│	e2 94 82	BOX DRAWINGS LIGHT VERTICAL
# U+2503	┃	e2 94 83	BOX DRAWINGS HEAVY VERTICAL
# U+2504	┄	e2 94 84	BOX DRAWINGS LIGHT TRIPLE DASH HORIZONTAL
# U+2505	┅	e2 94 85	BOX DRAWINGS HEAVY TRIPLE DASH HORIZONTAL
# U+2506	┆	e2 94 86	BOX DRAWINGS LIGHT TRIPLE DASH VERTICAL
# U+2507	┇	e2 94 87	BOX DRAWINGS HEAVY TRIPLE DASH VERTICAL
# U+2508	┈	e2 94 88	BOX DRAWINGS LIGHT QUADRUPLE DASH HORIZONTAL
# U+2509	┉	e2 94 89	BOX DRAWINGS HEAVY QUADRUPLE DASH HORIZONTAL
# U+250A	┊	e2 94 8a	BOX DRAWINGS LIGHT QUADRUPLE DASH VERTICAL
# U+250B	┋	e2 94 8b	BOX DRAWINGS HEAVY QUADRUPLE DASH VERTICAL
# U+250C	┌	e2 94 8c	BOX DRAWINGS LIGHT DOWN AND RIGHT
# U+250D	┍	e2 94 8d	BOX DRAWINGS DOWN LIGHT AND RIGHT HEAVY
# U+250E	┎	e2 94 8e	BOX DRAWINGS DOWN HEAVY AND RIGHT LIGHT
# U+250F	┏	e2 94 8f	BOX DRAWINGS HEAVY DOWN AND RIGHT
# U+2510	┐	e2 94 90	BOX DRAWINGS LIGHT DOWN AND LEFT
# U+2511	┑	e2 94 91	BOX DRAWINGS DOWN LIGHT AND LEFT HEAVY
# U+2512	┒	e2 94 92	BOX DRAWINGS DOWN HEAVY AND LEFT LIGHT
# U+2513	┓	e2 94 93	BOX DRAWINGS HEAVY DOWN AND LEFT
# U+2514	└	e2 94 94	BOX DRAWINGS LIGHT UP AND RIGHT
# U+2515	┕	e2 94 95	BOX DRAWINGS UP LIGHT AND RIGHT HEAVY
# U+2516	┖	e2 94 96	BOX DRAWINGS UP HEAVY AND RIGHT LIGHT
# U+2517	┗	e2 94 97	BOX DRAWINGS HEAVY UP AND RIGHT
# U+2518	┘	e2 94 98	BOX DRAWINGS LIGHT UP AND LEFT
# U+2519	┙	e2 94 99	BOX DRAWINGS UP LIGHT AND LEFT HEAVY
# U+251A	┚	e2 94 9a	BOX DRAWINGS UP HEAVY AND LEFT LIGHT
# U+251B	┛	e2 94 9b	BOX DRAWINGS HEAVY UP AND LEFT
# U+251C	├	e2 94 9c	BOX DRAWINGS LIGHT VERTICAL AND RIGHT
# U+251D	┝	e2 94 9d	BOX DRAWINGS VERTICAL LIGHT AND RIGHT HEAVY
# U+251E	┞	e2 94 9e	BOX DRAWINGS UP HEAVY AND RIGHT DOWN LIGHT
# U+251F	┟	e2 94 9f	BOX DRAWINGS DOWN HEAVY AND RIGHT UP LIGHT
# U+2520	┠	e2 94 a0	BOX DRAWINGS VERTICAL HEAVY AND RIGHT LIGHT
# U+2521	┡	e2 94 a1	BOX DRAWINGS DOWN LIGHT AND RIGHT UP HEAVY
# U+2522	┢	e2 94 a2	BOX DRAWINGS UP LIGHT AND RIGHT DOWN HEAVY
# U+2523	┣	e2 94 a3	BOX DRAWINGS HEAVY VERTICAL AND RIGHT
# U+2524	┤	e2 94 a4	BOX DRAWINGS LIGHT VERTICAL AND LEFT
# U+2525	┥	e2 94 a5	BOX DRAWINGS VERTICAL LIGHT AND LEFT HEAVY
# U+2526	┦	e2 94 a6	BOX DRAWINGS UP HEAVY AND LEFT DOWN LIGHT
# U+2527	┧	e2 94 a7	BOX DRAWINGS DOWN HEAVY AND LEFT UP LIGHT
# U+2528	┨	e2 94 a8	BOX DRAWINGS VERTICAL HEAVY AND LEFT LIGHT
# U+2529	┩	e2 94 a9	BOX DRAWINGS DOWN LIGHT AND LEFT UP HEAVY
# U+252A	┪	e2 94 aa	BOX DRAWINGS UP LIGHT AND LEFT DOWN HEAVY
# U+252B	┫	e2 94 ab	BOX DRAWINGS HEAVY VERTICAL AND LEFT
# U+252C	┬	e2 94 ac	BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
# U+252D	┭	e2 94 ad	BOX DRAWINGS LEFT HEAVY AND RIGHT DOWN LIGHT
# U+252E	┮	e2 94 ae	BOX DRAWINGS RIGHT HEAVY AND LEFT DOWN LIGHT
# U+252F	┯	e2 94 af	BOX DRAWINGS DOWN LIGHT AND HORIZONTAL HEAVY
# U+2530	┰	e2 94 b0	BOX DRAWINGS DOWN HEAVY AND HORIZONTAL LIGHT
# U+2531	┱	e2 94 b1	BOX DRAWINGS RIGHT LIGHT AND LEFT DOWN HEAVY
# U+2532	┲	e2 94 b2	BOX DRAWINGS LEFT LIGHT AND RIGHT DOWN HEAVY
# U+2533	┳	e2 94 b3	BOX DRAWINGS HEAVY DOWN AND HORIZONTAL
# U+2534	┴	e2 94 b4	BOX DRAWINGS LIGHT UP AND HORIZONTAL
# U+2535	┵	e2 94 b5	BOX DRAWINGS LEFT HEAVY AND RIGHT UP LIGHT
# U+2536	┶	e2 94 b6	BOX DRAWINGS RIGHT HEAVY AND LEFT UP LIGHT
# U+2537	┷	e2 94 b7	BOX DRAWINGS UP LIGHT AND HORIZONTAL HEAVY
# U+2538	┸	e2 94 b8	BOX DRAWINGS UP HEAVY AND HORIZONTAL LIGHT
# U+2539	┹	e2 94 b9	BOX DRAWINGS RIGHT LIGHT AND LEFT UP HEAVY
# U+253A	┺	e2 94 ba	BOX DRAWINGS LEFT LIGHT AND RIGHT UP HEAVY
# U+253B	┻	e2 94 bb	BOX DRAWINGS HEAVY UP AND HORIZONTAL
# U+253C	┼	e2 94 bc	BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
# U+253D	┽	e2 94 bd	BOX DRAWINGS LEFT HEAVY AND RIGHT VERTICAL LIGHT
# U+253E	┾	e2 94 be	BOX DRAWINGS RIGHT HEAVY AND LEFT VERTICAL LIGHT
# U+253F	┿	e2 94 bf	BOX DRAWINGS VERTICAL LIGHT AND HORIZONTAL HEAVY
# U+2540	╀	e2 95 80	BOX DRAWINGS UP HEAVY AND DOWN HORIZONTAL LIGHT
# U+2541	╁	e2 95 81	BOX DRAWINGS DOWN HEAVY AND UP HORIZONTAL LIGHT
# U+2542	╂	e2 95 82	BOX DRAWINGS VERTICAL HEAVY AND HORIZONTAL LIGHT
# U+2543	╃	e2 95 83	BOX DRAWINGS LEFT UP HEAVY AND RIGHT DOWN LIGHT
# U+2544	╄	e2 95 84	BOX DRAWINGS RIGHT UP HEAVY AND LEFT DOWN LIGHT
# U+2545	╅	e2 95 85	BOX DRAWINGS LEFT DOWN HEAVY AND RIGHT UP LIGHT
# U+2546	╆	e2 95 86	BOX DRAWINGS RIGHT DOWN HEAVY AND LEFT UP LIGHT
# U+2547	╇	e2 95 87	BOX DRAWINGS DOWN LIGHT AND UP HORIZONTAL HEAVY
# U+2548	╈	e2 95 88	BOX DRAWINGS UP LIGHT AND DOWN HORIZONTAL HEAVY
# U+2549	╉	e2 95 89	BOX DRAWINGS RIGHT LIGHT AND LEFT VERTICAL HEAVY
# U+254A	╊	e2 95 8a	BOX DRAWINGS LEFT LIGHT AND RIGHT VERTICAL HEAVY
# U+254B	╋	e2 95 8b	BOX DRAWINGS HEAVY VERTICAL AND HORIZONTAL
# U+254C	╌	e2 95 8c	BOX DRAWINGS LIGHT DOUBLE DASH HORIZONTAL
# U+254D	╍	e2 95 8d	BOX DRAWINGS HEAVY DOUBLE DASH HORIZONTAL
# U+254E	╎	e2 95 8e	BOX DRAWINGS LIGHT DOUBLE DASH VERTICAL
# U+254F	╏	e2 95 8f	BOX DRAWINGS HEAVY DOUBLE DASH VERTICAL
# U+2550	═	e2 95 90	BOX DRAWINGS DOUBLE HORIZONTAL
# U+2551	║	e2 95 91	BOX DRAWINGS DOUBLE VERTICAL
# U+2552	╒	e2 95 92	BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE
# U+2553	╓	e2 95 93	BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE
# U+2554	╔	e2 95 94	BOX DRAWINGS DOUBLE DOWN AND RIGHT
# U+2555	╕	e2 95 95	BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE
# U+2556	╖	e2 95 96	BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE
# U+2557	╗	e2 95 97	BOX DRAWINGS DOUBLE DOWN AND LEFT
# U+2558	╘	e2 95 98	BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE
# U+2559	╙	e2 95 99	BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE
# U+255A	╚	e2 95 9a	BOX DRAWINGS DOUBLE UP AND RIGHT
# U+255B	╛	e2 95 9b	BOX DRAWINGS UP SINGLE AND LEFT DOUBLE
# U+255C	╜	e2 95 9c	BOX DRAWINGS UP DOUBLE AND LEFT SINGLE
# U+255D	╝	e2 95 9d	BOX DRAWINGS DOUBLE UP AND LEFT
# U+255E	╞	e2 95 9e	BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE
# U+255F	╟	e2 95 9f	BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE
# U+2560	╠	e2 95 a0	BOX DRAWINGS DOUBLE VERTICAL AND RIGHT
# U+2561	╡	e2 95 a1	BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE
# U+2562	╢	e2 95 a2	BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE
# U+2563	╣	e2 95 a3	BOX DRAWINGS DOUBLE VERTICAL AND LEFT
# U+2564	╤	e2 95 a4	BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE
# U+2565	╥	e2 95 a5	BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE
# U+2566	╦	e2 95 a6	BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL
# U+2567	╧	e2 95 a7	BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE
# U+2568	╨	e2 95 a8	BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE
# U+2569	╩	e2 95 a9	BOX DRAWINGS DOUBLE UP AND HORIZONTAL
# U+256A	╪	e2 95 aa	BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE
# U+256B	╫	e2 95 ab	BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE
# U+256C	╬	e2 95 ac	BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL
# U+256D	╭	e2 95 ad	BOX DRAWINGS LIGHT ARC DOWN AND RIGHT
# U+256E	╮	e2 95 ae	BOX DRAWINGS LIGHT ARC DOWN AND LEFT
# U+256F	╯	e2 95 af	BOX DRAWINGS LIGHT ARC UP AND LEFT
# U+2570	╰	e2 95 b0	BOX DRAWINGS LIGHT ARC UP AND RIGHT
# U+2571	╱	e2 95 b1	BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT
# U+2572	╲	e2 95 b2	BOX DRAWINGS LIGHT DIAGONAL UPPER LEFT TO LOWER RIGHT
# U+2573	╳	e2 95 b3	BOX DRAWINGS LIGHT DIAGONAL CROSS
# U+2574	╴	e2 95 b4	BOX DRAWINGS LIGHT LEFT
# U+2575	╵	e2 95 b5	BOX DRAWINGS LIGHT UP
# U+2576	╶	e2 95 b6	BOX DRAWINGS LIGHT RIGHT
# U+2577	╷	e2 95 b7	BOX DRAWINGS LIGHT DOWN
# U+2578	╸	e2 95 b8	BOX DRAWINGS HEAVY LEFT
# U+2579	╹	e2 95 b9	BOX DRAWINGS HEAVY UP
# U+257A	╺	e2 95 ba	BOX DRAWINGS HEAVY RIGHT
# U+257B	╻	e2 95 bb	BOX DRAWINGS HEAVY DOWN
# U+257C	╼	e2 95 bc	BOX DRAWINGS LIGHT LEFT AND HEAVY RIGHT
# U+257D	╽	e2 95 bd	BOX DRAWINGS LIGHT UP AND HEAVY DOWN
# U+257E	╾	e2 95 be	BOX DRAWINGS HEAVY LEFT AND LIGHT RIGHT
# U+257F	╿	e2 95 bf	BOX DRAWINGS HEAVY UP AND LIGHT DOWN