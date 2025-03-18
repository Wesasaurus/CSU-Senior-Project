#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <list>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;

  const int KEY_LEFT = 'a', KEY_RIGHT = 'd',  KEY_UP = 'w', KEY_DOWN = 's';
  const int HEIGHT = 20, WIDTH = 20;
  
  struct Player{
    char sprite;
    int x;
    int y;
  };

  struct Array {
    unsigned char maze[HEIGHT][WIDTH] = {
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
    };
  };

  struct Riddles
  {
    string riddle;
    string answer;
  };

  // Selecting Riddle Type
  void gameType();

  // Parsing riddles
  int getData(Riddles list[], int count, string file);
  
  // Riddle Randomizing
  int random_r(int size);

  // Answering Riddle
  bool answer(Riddles list[], int random, string input);

  // Riddle functionality
  bool riddle(Riddles list[], int size);

  // Maze Generation
  Array randomMaze(Array Maze);

  // Maze Traversal
  void mazeTraverse(bool run, Player player, Array maze, int count, Riddles list[], int size);

int main()
{
  //Running the game
  gameType();
  
  return 0;
}

void gameType() {
  ifstream inFile;
    string word;
    string keyword;
    string file;
    string line;
    int count = 0;
    Player player;
    player.sprite = 'W';
    player.x = 0;
    player.y = 0;
    bool run = true;
    Array maze;
    int count2 = 0;
    const std::filesystem::path pathToShow{std::filesystem::current_path()};

    // Asking for File
    cout << "Here are a selection of riddle types to choose from:\n";
    for (const auto& entry : std::filesystem::directory_iterator(pathToShow)) {
      const auto filenameStr = entry.path().filename().string();
      if (entry.is_regular_file()) {
        if (filenameStr.find("Maze") != false) {
          std::cout << filenameStr << '\n';
        }
      }
    }
    cout << "Please type which one you would like to use: ";
    cin >> file;

    // Opening file to check it & to count number of lines
    inFile.open(file);

    // If file open fails rerun the program
    if (inFile.fail())
    {
      cout << file << " is an invalid option.\n";
      gameType();
    }
    while (!inFile.eof()) {
      getline(inFile, line);
      count++;
    }
    // Closing file
    inFile.close();

    count = count - 1;

    // Parsing file
	  Riddles list[count];
	  int amount[count] = {};
    int size = getData(list, count, file);

    // Run Maze
    maze = randomMaze(maze);

    // Selecting starting point on maze
    if (maze.maze[2][0] == ' ') {
      player.x = 0;
      player.y = 2;
    } else if (maze.maze[7][19] == ' ') {
      player.x = 19;
      player.y = 7;
    } else if (maze.maze[19][8] == ' ') {
      player.x = 8;
      player.y = 19;
    };

    // Allows for maze traversal
    mazeTraverse(run, player, maze, count2, list, size);
}

int getData(Riddles list[], int count, string file)
{
	// Define variables
	ifstream inFile;
	int dataCount = 0;
	string fileName = file;

	// Initialize Values
	for (int index = 0; index < count; ++ index)
	{
		list[index].riddle = to_string(index + 1);
		list[index].answer = to_string(index);
	}

	// Open file 
	inFile.open(fileName);

	// Grab data by looping through 2D array
	for (int index = 0; index < count; ++index)
	{
		getline(inFile, list[index].riddle, '\t');
		getline(inFile, list[index].answer, '.');
		inFile.ignore(INT_MAX, '\n');
		++dataCount;
		if (!inFile)
		{
			--dataCount;
			return dataCount;
		}
	}
	
	// Close file
	inFile.close();

	return dataCount;
}

// Generate random number
int random_r(int size) {
  int random;
  int range = size;
  srand(time(NULL));
  random = 0 + rand() % range;
  return random;
}

bool answer(Riddles list[], int random, string input) {    
  // Comparing answer key to input
  if (list[random].answer.compare(input) == 0) {
    if (input.size() < list[random].answer.size()) {
      cout << "Incorrect. Please try again." << endl;
      return false;
    }
    else {
      cout << "Correct!" << endl;
      return true;
    }
  }
  else {
  cout << "Incorrect." << endl;
  return false;
  }

  return false;
}

bool riddle(Riddles list[], int size) {
    // Randomizer
    int random = random_r(size);
    int chances = 3;

    // Answering riddle
    string input = "a";
    bool correct = false;
    cout << '\n' << "You have "<< chances << " total chances.";
    while (correct == false) {
      if (input != "") {
      cout << '\n' << list[random].riddle << endl;  
      }
      //std::cout << list[random].answer << ' ' << endl;
      getline(cin, input);
      //cout << input << '\n';
      
      // Checking answers
      if (input != "") {
      correct = answer(list, random, input);
      // Counting attempts remaining
      if (correct == false) {
        chances--;
        cout << "You have " << chances << " chances remaining." << endl;
          if (chances == 0) {
            cout << "Game Over!" << '\n';
            return false;
          }
        }
      }
    }
    return true;
}

Array randomMaze(Array maze){
  // Randomize the maze
  int amount = random_r(3);

  // Selecting maze based on randomization
  switch (amount){
    case 0: {
      maze = {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
        '#',' ','#',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',
        ' ',' ','#',' ','#',' ',' ',' ',' ','#',' ','#','#','#','#',' ','#',' ','#','#',
        '#',' ','#',' ','#','#','#','#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',
        '#',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#','#','#','#','#','#','#',
        '#',' ','#',' ','#','#',' ','#',' ','#',' ','#','#','#','#',' ',' ',' ','#','#',
        '#',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#','#','#',' ','#',' ','#','#',
        '#',' ','#',' ','#','#',' ','#',' ','#','#',' ',' ',' ',' ',' ','#',' ','#','#',
        '#',' ','#',' ',' ',' ',' ','#',' ','#','#',' ','#','#','#','#','#',' ','#','#',
        '#',' ','#','#','#','#','#','#',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ','#',
        '#',' ',' ',' ','#',' ',' ','#',' ','#','#','#','#',' ','#',' ','#','#',' ','#',
        '#','#','#',' ','#',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#','#',' ','#',
        '#',' ',' ',' ',' ',' ',' ','#','#',' ','#','#',' ','#','#',' ','#','#',' ','#',
        '#',' ','#','#','#','#',' ','#','#',' ',' ','#',' ','#','#',' ','#','#','#','#',
        '#',' ',' ',' ',' ','#',' ',' ','#','#',' ','#',' ','#','#',' ',' ',' ',' ','#',
        '#',' ','#','#',' ','#','#',' ',' ','#',' ',' ',' ','#','#','#','#','#',' ','#',
        '#',' ','#',' ',' ','#','#','#',' ','#',' ','#','#','#',' ',' ',' ','#',' ','X',
        '#',' ','#',' ','#','#',' ','#',' ','#',' ','#','#',' ',' ','#',' ','#','#','#',
        '#',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#','#',' ',' ',' ','#',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      };
      return maze;
    }
    case 1: {
      maze = {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
        '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',
        '#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ','#',
        '#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#',' ','#',
        '#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#',' ','#','#',' ','#',
        '#',' ','#','#',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#',' ',' ','#','#','#',
        '#',' ','#','#',' ','#','#','#','#','#','#',' ','#',' ','#','#',' ',' ','#','#',
        '#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#','#',' ',' ',' ',
        '#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#',
        '#',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#',' ',' ',' ','#',
        '#',' ',' ',' ','#',' ','#','#','#','#','#','#','#','#',' ',' ',' ','#',' ','#',
        '#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#','#',' ','#',
        '#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ','#',' ',' ',' ',' ','#',' ','#',
        '#','#','#','#','#','#','#',' ',' ',' ','#',' ','#',' ','#','#',' ','#',' ','#',
        '#',' ',' ',' ',' ',' ','#',' ','#','#','#',' ','#',' ','#',' ',' ','#',' ','#',
        '#',' ','#','#','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#','#',' ','#',
        '#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ',' ','#',
        '#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#','#',
        'X',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
      };
      return maze;
    }
    case 2: {
      maze  = {
        '#','#','#','#','#','#','X','#','#','#','#','#','#','#','#','#','#','#','#','#',
        '#','#',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',
        '#','#',' ','#',' ','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#',
        '#','#',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#',
        '#','#',' ','#',' ','#',' ','#',' ','#',' ','#','#','#','#',' ','#',' ',' ','#',
        '#',' ',' ','#',' ','#',' ','#','#','#',' ','#',' ',' ','#',' ','#',' ','#','#',
        '#','#',' ','#',' ','#',' ',' ',' ',' ',' ','#','#',' ','#',' ',' ',' ','#','#',
        '#',' ',' ','#',' ','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#',
        '#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',
        '#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
        '#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#',
        '#','#',' ','#',' ','#','#',' ','#','#','#','#',' ','#',' ',' ',' ',' ','#','#',
        '#','#',' ',' ',' ','#','#',' ','#','#',' ','#',' ','#',' ','#',' ','#','#','#',
        '#','#',' ','#','#','#','#',' ','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',
        '#','#',' ','#',' ',' ',' ',' ','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',
        '#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',
        '#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ','#',
        '#',' ','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#',
        '#',' ','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
        '#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',
      };
      return maze;
    }
  }
  return maze;
}

void mazeTraverse(bool run, Player player, Array maze, int count, Riddles list[], int size) {
  // While program is running reprint the maze with new player location
  while (run == true) {
    // Replaces empty space with player character
      if (maze.maze[player.y][player.x] == ' ') {
        maze.maze[player.y][player.x] = player.sprite;
      }
      // Replaces Exit with a V for Victory
      else if (maze.maze[player.y][player.x] == 'X') {
        maze.maze[player.y][player.x] = 'V';
        cout << "\nVictory!\n";
        run = false;
      }
      for (int y = 0; y < HEIGHT; y++) {
        cout << endl;
        for (int x = 0; x < WIDTH; x++) {
          cout << maze.maze[y][x];
        }
      }
      // Gets WASD input without the need to press enter every time
      char input = getch();
      switch (input) {
        case KEY_LEFT: {
          if (maze.maze[player.y][player.x-1] != '#') {
            maze.maze[player.y][player.x] = ' ';
            player.x--;
          }
          break;
        }
        case KEY_RIGHT: {
          if (maze.maze[player.y][player.x+1] != '#') {
            maze.maze[player.y][player.x] = ' ';
            player.x++;
          }
          break;
        }
        case KEY_UP: {
          if (maze.maze[player.y-1][player.x] != '#') {
            maze.maze[player.y][player.x] = ' ';
            player.y--;
          }
          break;
        }
        case KEY_DOWN: {
          if (maze.maze[player.y+1][player.x] != '#') {
            maze.maze[player.y][player.x] = ' ';
            player.y++;
          }
          break;
        }
        //Quit button for testing purposes
        case 'e': {
          exit(0);
        }
      }
      //Clears screen every time you move in maze for a more fluid viewing experience
      system("cls");
      //Interval at which riddles appear
      if (count == 15) {
        run = riddle(list, size);
        count = 0;
      }
      else {
        count++;
      }
  }
}