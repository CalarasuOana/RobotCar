# Controlul-unui-robot-mobil-folosind-Arduino
Aceasta este o colecție de coduri sursă pentru proiectul meu „Controlul unui robot mobil folosind Arduino”. Codurile furnizate includ programe pentru efectuarea manevrelor pe traseu, dar și controlarea robotului mobil prin aplicatia „RoboMasina Control” implementata in Android Studio. 

Ghid pentru instalarea aplicației Arduino:

	1. Accesați site-ul oficial Arduino: https://www.arduino.cc/
	2. Navigați la pagina de descărcare: https://www.arduino.cc/en/software
	3. Selectați versiunea potrivită pentru sistemul de operare pe care îl utilizați (Windows, macOS, Linux).
	4. Făcând clic pe versiunea selectată, veți fi redirecționat către pagina de descărcare corespunzătoare.
	5. Descărcați fișierul de instalare pe computer.
	6. După finalizarea descărcării, deschideți fișierul de instalare.
	7. Urmați instrucțiunile de instalare furnizate de asistentul de instalare.
	8. Selectați locația de instalare a aplicației Arduino (dacă este necesar).
	9. Finalizați instalarea prin urmarea pașilor.
	10.După instalare, deschideți aplicația Arduino.
	11.Conectați placa Arduino Mega la computer utilizând un cablu USB.
	12.Selectați tipul de plăci Arduino utilizate din meniul "Tools" (Instrumente) -> "Board" (Placă).
	13. Alegeți portul serial corespunzător la care este conectată placa Arduino din meniul "Tools" -> "Port".
	14. Aplicația Arduino este acum instalată și configurată pentru a programa și comunica cu placa masinuta Arduino.

Pentru instalarea bibliotecilor urmati pasii urmatori:

	1. Accesați meniul "Sketch" (Schiță) și apoi "Include Library" (Includere bibliotecă).
	2. Apare o listă cu biblioteci disponibile. Cautati bibliotecile „spi.h”, „MFRC522”, „Adafruit_GFX”, „Adafruit_SSD1306” pe rand.
	3. Când găsiți biblioteca dorită, faceți clic pe numele acesteia pentru a deschide fereastra de instalare.
	4. În fereastra de instalare, verificați versiunea și faceți clic pe butonul "Install" (Instalare) pentru a instala biblioteca.
	5. Așteptați ca instalarea să se încheie. Puteți vedea progresul în bara de stare din partea de jos a ferestrei Arduino IDE.
	6. După finalizarea instalării, biblioteca va fi disponibilă pentru a fi utilizată în proiectul meu „Controlul unui robot mobil folosind Arduino”.

Ghid pentru compilarea codului in Arduino:

	1. Pentru ca mașinuța să urmăreasca traseu folosiți fisierul „traseu_complet_robot_mobil”.
	2. Deschideți fișierul de cod sursă în Arduino IDE. Puteți face acest lucru prin intermediul meniului "File" (Fișier) -> "New" (Nou) sau "File" (Fișier) -> "Open" (Deschideți) pentru a selecta fișierul ”traseu_complet_robot_mobil”.
	3. Puteți rula programul pe placa Arduino făcând clic pe butonul "Upload" (Încărcare) din bara de instrumente sau utilizând combinația de taste "Ctrl + U". Arduino IDE va compila programul și îl va încărca pe placa Arduino conectată.
	4. După ce a fost compilat, veti vedea in ”Serial monitor” starile robotului mobil si afisarea valorilor primite de la senzori.
  	5. Pentru aflarea codului uid al tag-ului RFID trebuie incarcat fisierul „verificare_uid_tag” pe placa Arduino Mega cu ajutorul aplicației Android Studio, iar apoi trebuie pus tag-ul pe cititorul RFID, iar in Serial Monitor va fi afișat uid-ul.
	6. Pentru a controla masinuta prin aplicatia RoboMasina Control, descarcati fisierul „conexiune_RoboMasinaControl” si urmati pasii de mai sus, dar aceasta functionalitate va fi posibila doar prin intermediul aplicației mobile utilizată în Android Studio. 

Ghid pentru instalarea aplicatiei Android Studio

	1. Accesați site-ul oficial Android Studio: https://developer.android.com/studio
	2. Faceți clic pe butonul "Download" pentru a descărca fișierul de instalare.
	3. După finalizarea descărcării, deschideți fișierul de instalare.
	4. Veți fi întâmpinat de un asistent de instalare. Faceți clic pe "Next" (Următorul) pentru a continua.
	5. Alegeți locația de instalare a Android Studio pe computer. Puteți selecta locația implicită sau puteți alege una personalizată. Apoi faceți clic pe "Next".
	6. Selectați componentele pe care doriți să le instalați. De obicei, puteți lăsa selecția implicită și să faceți clic pe "Next".
	7.Alegeți tema de culoare pentru interfața Android Studio și faceți clic pe "Next".
	8. În fereastra următoare, asistentul de instalare vă va prezenta opțiunea de a instala Android Virtual Device (AVD). Puteți lăsa caseta bifată dacă doriți să creați și să rulați emulatoare Android pe computer. Faceți clic pe "Next".
	9. Verificați setările finale și faceți clic pe "Finish" pentru a începe instalarea.
	10. Android Studio va începe să descarce componentele necesare și să finalizeze instalarea.
	11. După finalizarea instalării, lansați Android Studio.
	12. Configurarea inițială a Android Studio vă va solicita să acceptați Termenii și Condițiile și să alegeți setările de configurare. Urmați instrucțiunile și finalizați configurarea inițială.
	13. Navigați la locația unde este salvat proiectul Android Studio și selectați dosarul principal al proiectului numit „robotcar”.
	14. Faceți clic pe butonul "OK" pentru a deschide proiectul în Android Studio.
	15. Așteptați ca Android Studio să importe și să construiască proiectul. Aceasta poate dura câteva momente, în funcție de dimensiunea și complexitatea proiectului.
	16. După finalizarea procesului de importare, veți vedea structura proiectului în panoul "Project" (Proiect) din partea stângă a ecranului. Acolo puteți naviga prin fișierele proiectului și puteți accesa diverse componente și resurse.
	17. Pentru rularea proiectului apasati pe tab-ul de RUN -> run „app” 


