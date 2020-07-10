message_manager_src_path = MessageManager/src
message_manager_include_path = MessageManager/include
io_manager_src_path = IOManager/src
io_manager_include_path = IOManager/include
game_manager_src_path = GameManager/src
game_manager_include_path = GameManager/include
map_display_src_path = MapDisplay/src
map_display_include_path = MapDisplay/include
log_display_src_path = LogDisplay/src
log_display_include_path = LogDisplay/include
stats_display_src_path = StatsDisplay/src
stats_display_include_path = StatsDisplay/include

all: mapDisplay logDisplay statsDisplay gameManager ioManager messageManager

messageManager:
	g++ -std=c++1z -o bin/RobotCommander MessageManager/main.cpp $(message_manager_src_path)/MessageManager.cpp $(message_manager_src_path)/ConfigManager.cpp $(game_manager_src_path)/ScreenManager.cpp $(io_manager_src_path)/Sender.cpp $(message_manager_include_path)/MessageManager.h $(message_manager_include_path)/ConfigManager.h $(game_manager_include_path)/ScreenManager.h $(io_manager_include_path)/Sender.h

ioManager:
	g++ -std=c++1z -o bin/IOManager IOManager/main.cpp $(io_manager_src_path)/IOManager.cpp $(message_manager_src_path)/ConfigManager.cpp $(io_manager_src_path)/Sender.cpp $(io_manager_include_path)/IOManager.h $(message_manager_include_path)/ConfigManager.h $(message_manager_include_path)/MessageManager.h $(io_manager_include_path)/Sender.h

gameManager:
	g++ -std=c++1z -o bin/GameManager GameManager/main.cpp $(game_manager_src_path)/GameManager.cpp $(message_manager_src_path)/ConfigManager.cpp $(game_manager_src_path)/Map.cpp $(game_manager_src_path)/ScreenManager.cpp $(game_manager_src_path)/Player.cpp $(game_manager_src_path)/Enemy.cpp $(io_manager_src_path)/Sender.cpp $(game_manager_src_path)/Robot.cpp $(game_manager_src_path)/Point.cpp $(game_manager_include_path)/GameManager.h $(message_manager_include_path)/ConfigManager.h $(game_manager_include_path)/Map.h $(game_manager_include_path)/ScreenManager.h $(game_manager_include_path)/Player.h $(game_manager_include_path)/Enemy.h $(io_manager_include_path)/Sender.h $(game_manager_include_path)/Robot.h $(game_manager_include_path)/Point.h

mapDisplay:
	g++ -std=c++1z -o bin/MapDisplay $(map_display_src_path)/MapDisplay.cpp $(message_manager_src_path)/ConfigManager.cpp $(map_display_include_path)/Colors.h $(game_manager_include_path)/Directions.h $(message_manager_include_path)/ConfigManager.h

logDisplay:
	g++ -std=c++1z -o bin/LogDisplay $(log_display_src_path)/LogDisplay.cpp $(message_manager_src_path)/ConfigManager.cpp $(map_display_include_path)/Colors.h $(message_manager_include_path)/ConfigManager.h

statsDisplay:
	g++ -std=c++1z -o bin/StatsDisplay $(stats_display_src_path)/StatsDisplay.cpp $(message_manager_src_path)/ConfigManager.cpp $(map_display_include_path)/Colors.h $(message_manager_include_path)/ConfigManager.h

clean:
	rm -f bin/*
