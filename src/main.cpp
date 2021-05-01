#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "ECS/Entity.h"
#include "ECS/Components/Transform.h"
#include "ECS/EntityManager.h"

int main() {
  EntityManager* manager = new EntityManager();

  Entity* entity = new Entity();
  manager->AddEntity(entity);

  // while (true) {
  //   manager->Update();
  //   manager->Draw();
  // }

  entity->GetComponent<Transform>().Position = Vector2DFloat(300, 200);
  std::cout << entity->GetComponent<Transform>().Position << std::endl;
  std::cout << entity->HasComponent<Transform>() << std::endl;

  manager->EraseEntity(entity);

  // constexpr std::size_t kFramesPerSecond{60};
  // constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  // constexpr std::size_t kScreenWidth{640};
  // constexpr std::size_t kScreenHeight{360};

  // Renderer renderer(kScreenWidth, kScreenHeight);
  // Controller controller;
  // Game game;
  // game.Run(controller, renderer, kMsPerFrame);
  // std::cout << "Game has terminated successfully!\n";
  // std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}