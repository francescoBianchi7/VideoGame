il videogame è stato creato in c++ usando le librerie fornite da SFML.
Inoltre sono state usate le librerie di c++ random per il movimento dell'AI
map per la TileMap, Buttons, e le supportekeys
string per conversione, e lettura da file di testo 
cmath per operazioni matematiche
stack per muoversi agilmente tra gli stati
vector per i proiettili e gli Zombie e per poter cambiare la grandezza della finestra.

Il VideoGame si divide in 4 stati: MainMenu da cui si può accedere agli altri, GameState EditorState e SettingState.
in Editor state è possibile modificare la mappa scegliendo e posizionando le Tiles
![2022-09-16 11-27-23](https://user-images.githubusercontent.com/81578895/190615222-f17d7566-6b5b-40e2-995a-2981d3f317f5.gif)
![2022-09-16 11-27-23 (1)](https://user-images.githubusercontent.com/81578895/190615435-e8af505f-92c8-4fbc-a9a1-d2994291478d.gif)

Inoltre è possibile scegliere se hanno collision e posizionare EnemySpawners![2022-09-16 11-43-48](https://user-images.githubusercontent.com/81578895/190615725-8c8c5641-414f-4e84-9acf-951a2372c245.gif)
![2022-09-16 11-27-23 (2)](https://user-images.githubusercontent.com/81578895/190615779-3fffe81a-5bea-48a4-932d-debeabf78f46.gif)
