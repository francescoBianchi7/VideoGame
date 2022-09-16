The videogame is made in c++ using the multimedia libraries taken from SFML.
the c++ libraries used are: 
random for AI movement
map for the tiles in TileMap, Buttons, and Supportekeys
string for Gui.
cmath per operazioni matematiche
stack to easily switch between states.
vector for projectiles and Zombies, and also to save the various videoModes in Setting State(the only way to go fullScreen is by setting the third row of graphics.ini to 1 instead of 0).
   
The Game is Divided in 4 States: MainMenu is the starting state from which you can access GameState EditorState and SettingState.
in EditorState you can modify the map by placing and removing Tiles.
Le keys supportate sono:
          T aumenta tyle type (solo type 0 e 2 sono usati) R per diminuire
          C collisione
          Directional Arrows to switch between tile Textures
          LMB place Tile RMB remove Tile

![2022-09-16 11-27-23](https://user-images.githubusercontent.com/81578895/190615222-f17d7566-6b5b-40e2-995a-2981d3f317f5.gif)
![2022-09-16 11-27-23 (1)](https://user-images.githubusercontent.com/81578895/190615435-e8af505f-92c8-4fbc-a9a1-d2994291478d.gif)

Inoltre è possibile scegliere di posizionare EnemySpawners,evidenziate in blue(non hanno texture). oppure una tile hanno collision(in questo state sono evidenziate in rosso e posizionare 
![2022-09-16 11-43-48](https://user-images.githubusercontent.com/81578895/190615725-8c8c5641-414f-4e84-9acf-951a2372c245.gif)
![2022-09-16 11-27-23 (2)](https://user-images.githubusercontent.com/81578895/190615779-3fffe81a-5bea-48a4-932d-debeabf78f46.gif)
