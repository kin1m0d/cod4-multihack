﻿================================================================================
    MICROSOFT FOUNDATION CLASS-BIBLIOTHEK: MFC_Hack_Prototyp-Projektübersicht
===============================================================================

Diese MFC_Hack_Prototyp-Anwendung wurde vom Anwendungs-Assistenten für Sie erstellt. Diese Anwendung zeigt nicht nur die Grundlagen der Verwendung von Microsoft Foundation Classes, sondern dient auch als Ausgangspunkt für das Schreiben Ihrer Anwendung.

Diese Datei bietet eine Übersicht über den Inhalt der einzelnen Dateien, aus
denen Ihre MFC_Hack_Prototyp-Anwendung besteht.

MFC_Hack_Prototyp.vcxproj
    Dies ist die Hauptprojektdatei für VC++-Projekte, die mit dem Anwendungs-Assistenten generiert werden. Sie enthält Informationen über die Version von Visual C++, mit der die Datei generiert wurde, sowie über die Plattformen, Konfigurationen und Projektfunktionen, die im Anwendungs-Assistenten ausgewählt wurden.

MFC_Hack_Prototyp.vcxproj.filters
    Dies ist die Filterdatei für VC++-Projekte, die mithilfe eines Anwendungs-Assistenten erstellt werden. Sie enthält Informationen über die Zuordnung zwischen den Dateien im Projekt und den Filtern. Diese Zuordnung wird in der IDE zur Darstellung der Gruppierung von Dateien mit ähnlichen Erweiterungen unter einem bestimmten Knoten verwendet (z. B. sind CPP-Dateien dem Filter "Quelldateien" zugeordnet).

MFC_Hack_Prototyp.h
    Dies ist die Hauptheaderdatei für die Anwendung.
    Sie enthält andere projektspezifische Header (einschließlich Resource.h) und deklariert die HackApp-Anwendungsklasse.

MFC_Hack_Prototyp.cpp
    Dies ist die wichtigste Anwendungsquelldatei, die die Anwendungsklasse HackApp enthält.

MFC_Hack_Prototyp.rc
    Dies ist eine Auflistung aller vom Programm verwendeten Microsoft Windows-Ressourcen. Sie enthält die Symbole, Bitmaps und Cursor, die im Unterverzeichnis "RES" gespeichert werden. Diese Datei kann direkt in Microsoft Visual C++ bearbeitet werden. Ihre Projektressourcen befinden sich in 1031.

res\MFC_Hack_Prototyp.ico
    Dies ist eine Symboldatei, die als Anwendungssymbol verwendet wird. Dieses Symbol ist in der Hauptressourcendatei MFC_Hack_Prototyp.rc enthalten.

res\MFC_Hack_Prototyp.rc2
    Diese Datei enthält Ressourcen, die nicht von Microsoft Visual C++ bearbeitet werden. Sie sollten alle Ressourcen, die nicht mit dem Ressourcen-Editor bearbeitet werden können, in dieser Datei platzieren.


/////////////////////////////////////////////////////////////////////////////

Der Anwendungs-Assistent erstellt eine Dialogfeldklasse:

HackDlg.h, HackDlg.cpp - das Dialogfeld
    Diese Dateien enthalten Ihre HackDlg-Klasse. Diese Klasse definiert das Verhalten des Hauptdialogfelds der Anwendung. Die Vorlage für das Dialogfeld befindet sich in MFC_Hack_Prototyp.rc und kann in Microsoft Visual C++ bearbeitet werden.

/////////////////////////////////////////////////////////////////////////////

Andere Funktionen:

ActiveX-Steuerelemente
    Die Anwendung bietet Unterstützung für ActiveX-Steuerelemente.

/////////////////////////////////////////////////////////////////////////////

Andere Standarddateien:

StdAfx.h, StdAfx.cpp
    Mit diesen Dateien werden eine vorkompilierte Headerdatei (PCH) mit dem Namen MFC_Hack_Prototyp.pch und eine vorkompilierte Typendatei mit dem Namen StdAfx.obj erstellt.

Resource.h
    Dies ist die Standardheaderdatei, die neue Ressourcen-IDs definiert. Die Datei wird mit Microsoft Visual C++ gelesen und aktualisiert.

MFC_Hack_Prototyp.manifest
	Anwendungsmanifestdateien werden von Windows XP verwendet, um die Abhängigkeit einer Anwendung von bestimmten Versionen paralleler Assemblys zu beschreiben. Das Ladeprogramm verwendet diese Informationen, um die entsprechende Assembly aus dem Assemblycache oder privat von der Anwendung zu laden. Das Anwendungsmanifest kann zur Neuverteilung als externe .manifest-Datei einbezogen werden, die im selben Ordner wie die ausführbare Datei der Anwendung installiert ist, oder sie wird der ausführbaren Datei in Form einer Ressource hinzugefügt.
/////////////////////////////////////////////////////////////////////////////

Weitere Hinweise:

Der Anwendungs-Assistent weist Sie mit "TODO:"-Kommentaren auf Teile des Quellcodes hin, die Sie ergänzen oder anpassen sollten.

Wenn Ihre Anwendung MFC in einer gemeinsam genutzten DLL verwendet, müssen die MFC-DLLs mitverteilt werden. Wenn Ihre Anwendung eine andere Sprache als Systemsprache verwendet, müssen auch die entsprechende mfc110XXX.DLL für die lokalisierten Ressourcen mitverteilt werden.
Weitere Informationen zu diesen beiden Themen finden Sie im Abschnitt zur Neuverteilung von Visual C++-Anwendungen in der MSDN-Dokumentation.

/////////////////////////////////////////////////////////////////////////////
