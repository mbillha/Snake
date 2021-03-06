#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <memory>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int GetHighScore(std::string filename)
{
  int score = 0;
  std::string value;
  std::string line;
  std::string key;
  std::ifstream filestream(filename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "HighScore") {
          score = std::stoi(value);
          return score;
        }
      }
    }
  }
  return score;
}

void SaveHighScore(std::string filename, int highScore)
{
    std::fstream output_fstream;

    output_fstream.open(filename, std::ios_base::out);
    if (!output_fstream.is_open()) {
        // if not open, try to create Path:
        if (mkdir("../usr_data", 0777) == -1)
        {
          std::cerr << "Failed to open and create " << filename << '\n';
        }
        else
        {
          output_fstream.open(filename, std::ios_base::out);
          if (output_fstream.is_open()) output_fstream << "HighScore " << highScore << std::endl;
        }
    } 
    else 
    {
        output_fstream << "HighScore " << highScore << std::endl;
    }
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  const std::string fHighscore = "../usr_data/highscore.txt";

  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  std::unique_ptr<Controller> controller = std::make_unique<Controller>();
  std::unique_ptr<Game> game = std::make_unique<Game>(kGridWidth, kGridHeight);
  game.get()->Run(std::move(controller), std::move(renderer), kMsPerFrame);

  int highScore = GetHighScore(fHighscore);

  std::cout << "Game has terminated successfully!\n";
  if (highScore < game.get()->GetScore())
  {
    std::cout << "NEW HIGHSCORE!" << std::endl;
    SaveHighScore(fHighscore, game.get()->GetScore());
  }
  std::cout << "Score: " << game.get()->GetScore() << "\n";
  std::cout << "Size: " << game.get()->GetSize() << "\n";
  return 0;
}