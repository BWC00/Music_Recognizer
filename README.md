# Audio Recognizer
Muziekherkenningsautomaat geïmplementeerd met het Boyer Moore Horspool algoritme voor het vak Talen en Automaten.
Project gemaakt door Cédric Leclercq, Mohammed Shakleya, Robbe Nooyens en Victor van Herel.

## Installatie en gebruik
Download de repository en build het project via cmake (standaard C++ 17). Eens het programma runt, kun je met behulp van commandos instructies uitvoeren. De lijst met beschikbare commandos kan je raadplegen door 'help' in de voeren. Naast cmake moet je ook Qt 5.15.2 geïnstalleerd hebben.<br>

## Visualizatie
Om de automaten te visualizeren, download je graphviz via het commando 'sudo apt install graphviz'.
Daarna kan je met `dot -Tpng <input-file> -o <output-file[.png]>` de dotfile omzetten naar een afbeelding van de automaat.
Het genereren van de nodige `.dot`-bestanden kan enkel via de terminal-versie van de applicatie.

## Inleiding
Tegenwoordig wordt er zoveel muziek geproduced dat het haast onmogelijk is om elk liedje foutloos mee te kunnen zingen, laat staan dat je alle titels kent. Enkele jaren geleden kwam er een oplossing voor dit probleem nadat onze landgenoot Philip Inghelbrecht met enkele anderen Shazam oprichtte. Met deze app kan je op basis van een kort geluidsfragment een liedje achterhalen in een mum van tijd. Als een doorsnee gebruiker sta je er natuurlijk niet stil hoe deze app intern werkt. Als je geïnteresseerd bent in computers en programmeren kun je al beginnen speculeren en als je dan ook nog leert over automaten, kan je niet anders dan het hele project al voor je te zien!

## Algemene omschrijving project
Ons project wordt dus een eigen versie van Shazam. Onze focus zal liggen op het exact herkennen van audiomateriaal. Het kan bijvoorbeeld dat je je helemaal kan uitleven op een bepaalde beat van een liedje die in totaal maar een aantal seconden duurt. Ons programma zal dan op zoek gaan naar de titel van je liedje!

## Toepassing op de leerstof
Automaten zijn hier een uitstekende hulp voor. Denk bijvoorbeeld maar aan het concept van reguliere expressies, alleen bestaat onze regex dan uit een muziekpatroon en is de string waarin we zoeken niet langer een tekst maar een audiobestand.
Reguliere expressies gebruiken zou hier dus een logische keuze zijn, mocht het niet zijn dat we liefst een snellere methode zouden kunnen gebruiken. Na wat onderzoek te hebben gedaan, hebben we beslist hiervoor het Boyer-Moore automaat te gebruiken. Deze benadering zal ervoor zorgen dat we iets meer tijd zullen moeten besteden aan preprocessing, maar op langere termijn zullen de voordelen van deze keuze snel duidelijk worden.

## Korte omschrijving Boyer-Moore algoritme
Wat is nu precies het Boyer-Moore algoritme? Dit algoritme is een pattern matching algoritme dat ontwikkeld is met het doel veel efficiënter een bepaalde string van karakters in een groot tekstbestand te vinden, van websites tot PDF files.
Het algoritme zoekt dus de voorkomens van een gegeven input, typisch een kort stuk, in een veel langere tekst. De efficiëntie haalt het algoritme uit een volledige herziene manier van opzoeken, het gebruikt specifieke heuristieken om bepaalde situaties waarin met zekerheid geen match voorkomt vanaf het begin van deze situatie over te slaan.

## Parsing en gebruik van spectrogram
We kunnen echter niet zomaar loepzuivere audiobestanden in onze Boyer-Moore automaat duwen. Om ervoor te zorgen dat het automaat de audio kan verwerken, moeten we deze eerst parsen naar een string van karakters die een betekenis hebben. Voor dat we beginnen met het omzetten naar een string zetten we de audio om van stereo naar mono-audio. Dit neemt veel minder opslag in en maakt de string ook substantieel korter. Vervolgens maken we gebruik van de een library die '.wav' files kan omzetten naar samples (in de vorm van een vector van doubles). Hier na mappen we bepaalde ranges van doubles op karakters van een alphabet en zetten we elke double om in zijn corresponderende karakter. Ten slotte compressen we de string.

## Referenties
Baeza-Yates, R., Choffrut, C., & H. Gonnet, G. (1994, November). On Boyer-Moore Automata. Researchgate. https://www.researchgate.net/publication/2857447_On_Boyer-Moore_Automata

adamstark. (2017, February 1). adamstark/AudioFile. Github. https://github.com/adamstark/AudioFile

Mike Slade. (2014, January 13). Boyer Moore Horspool Algorithm [Video]. YouTube. https://www.youtube.com/watch?v=PHXAOKQk2dw
