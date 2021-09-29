Another university project (Hardwarenahe Programmierung, University of Düsseldorf).
It's basically a dungeon game developed entirely in C.
NOTE: The tests were already written by Prof. Dr. Stefan Conrad.

A snippet from the Aufgabenstellung:
•Ihr Programm soll eine Datei entgegennehmen, in der ein Level des Dungeon gespeichert ist.
Ein Level besteht aus:
(a) Mindestens einem Ausgang, dargestellt durch das Zeichen ”A“.
(b) Genau einer Spielfigur, dargestellt durch das Zeichen ”S“.
(c) W ̈anden, dargestellt durch das Zeichen ”#“.
(d) Leeren Feldern, dargestellt durch Leerzeichen.
(e) Einer Anzahl an Monstern, dargestellt durch eines der Zeichen ”<>vˆ“.

########
#  S   #
#    < #
#  A   #
########
Abbildung 2: Beispiel mit Spielfigur ”S“, Ausgang ”A“ und einem Monster ”<“, das nach Links schaut.

•Weiterhin soll das Programm Steuer-Befehle  ̈uber die Kommandozeile oder eine Datei entgegen-
nehmen können.
•Nachdem ein Befehl verarbeitet wurde, soll das Level auf der Standardausgabe oder in eine Datei
ausgegeben werden.
•Zusätzlich soll davor die Anzahl der bisher verarbeiteten Befehle und der zuletzt verarbeitete
Befehl ausgegeben werden.
•Zu Beginn des Levels soll das Spielfeld ebenfalls einmal ausgegeben werden.
Die Höhe und Breite der Level ist unbeschränkt.


Spielfigur:
Die Spielfigur (S) wird durch die folgenden Befehle gesteuert:
•”w“: Ein Feld nach Oben gehen.
•”a“: Ein Feld nach Links gehen.
•”s“: Ein Feld nach Unten gehen.
•”d“: Ein Feld nach Rechts gehen.
Nach der Eingabe eines Zeilenumbruchs sollen die Befehle verarbeitet werden. Die Eingabe von EOF
beendet das Spiel. Andere Eingaben als wasd, Zeilenumbruch und EOF sollen ignoriert werden.
Spielfiguren können auf allen Nicht-Wand-Feldern laufen


Ausgänge:
Nachdem eine Spielfigur einen Ausgang betritt, soll sich das Programm beenden und die Nachricht
”Gewonnen!“ ausgeben. Die Spielfigur wird in diesem Fall nicht mehr angezeigt, da sie den Ausgang
bereits in die Freiheit durchschritten hat.


Aufruf des Programms:
•Das Programm kriegt beim Aufruf optional den Namen der Level-Datei  ̈ubergeben. Falls keine
Datei  ̈ubergeben wurde soll das Level in der Datei level/1.txt ge ̈offnet werden.
•Die Eingabe-Datei mit Befehlen wird mit -i spezifiziert. Falls keine Eingabedatei übergeben
wurde, wird die Standardeingabe verwendet.
•Die Ausgabe-Datei mit Befehlen wird mit -o spezifiziert. Falls keine Ausgabedatei übergeben
wurde, wird die Standardausgabe verwendet.
Einige Beispiel-Aufrufe:
./dungeon
./dungeon -i eingabe.txt
./dungeon -o ausgabe.txt
./dungeon -i eingabe.txt -o ausgabe.txt level.txt
./dungeon level.txt -i eingabe.txt -o ausgabe.txt
