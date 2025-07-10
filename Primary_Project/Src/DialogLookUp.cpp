#include "DialogLookUp.h"

SCENESTR loadScenes(CSTR& filePath)
{
	ifstream file(filePath);
	string line;

	unordered_map<string, Scene> scenes;

	Scene currentScene;

	bool readingChoices = false;

	while (std::getline(file, line))
	{
		if (line.empty()) continue;


		if (line.rfind("@scene", 0) == 0)
		{
			if (!currentScene.id.empty())
				scenes[currentScene.id] = currentScene;
			currentScene = Scene();
			currentScene.id = line.substr(7);
			readingChoices = false;
		}

		else if (line.rfind("@emotion", 0) == 0)
		{
			currentScene.emotion = line.substr(9);
		}
		else if (line == "@choice")
		{
			readingChoices = true;
		}
		else if (readingChoices && line[0] == '-')
		{
			size_t arrow = line.find("=>");
			if (arrow != std::string::npos) {

				Choice choice;
				choice.text = line.substr(2, arrow - 3);
				choice.targetScene = line.substr(arrow + 3);
				currentScene.choices.push_back(choice);

			}
		}
		else if (line.front() == '"') {
			currentScene.lines.push_back(line.substr(1, line.size() - 2));
		}
	}

	if (!currentScene.id.empty())
		scenes[currentScene.id] = currentScene;

	return scenes;
}

void runScriptedStory(SCENESTR& scenes, CSTR& startScene)
{
	std::string current = startScene;

	while (!current.empty()) {
		auto it = scenes.find(current);
		if (it == scenes.end()) {
			std::cout << "Scene not found: " << current << "\n";
			return;
		}

		const Scene& scene = it->second;
		std::cout << "[Emotion: " << scene.emotion << "]\n";

		for (const std::string& line : scene.lines)
			std::cout << scene.emotion << " > " << line << '\n';

		if (!scene.choices.empty()) {
			std::cout << "\nWhat will you do?\n";
			for (size_t i = 0; i < scene.choices.size(); ++i) {
				std::cout << "  [" << (i + 1) << "] " << scene.choices[i].text << '\n';
			}

			int choice = 0;
			while (true) {
				std::cout << "\n> ";
				std::cin >> choice;
				if (choice >= 1 && choice <= static_cast<int>(scene.choices.size())) break;
				std::cout << "Invalid choice. Try again.\n";
			}
			std::cin.ignore(); // clear newline
			current = scene.choices[choice - 1].targetScene;
		}
		else {
			std::cout << "\n[Press Enter to continue...]\n";
			std::cin.get();
			current = ""; // or allow scene to define next
		}
	}
}

void SceneStart()
{
	SCENESTR scenes = loadScenes("story.script");
	runScriptedStory(scenes, "START");
}
