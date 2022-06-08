#include "App.h"

App::App()
	: m_trainingDataIdx(0U), m_epochIdx(1U)
{
	initWindow();
	loadData();
	initNet();
	initDataPointRenderer();
}

void App::run()
{
	while (m_window.isOpen())
	{
		update();
		render();
	}
}

void App::initWindow()
{
	std::string path = "config/graphics.ini";

	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "CANNOT OPEN: " << path << '\n';
		exit(-17);
	}

	std::string title;
	unsigned width, height;
	unsigned frameRateLimit;
	bool verticalSyncEnabled;
	sf::Vector2i position;

	getline(file, title);
	file >> width >> height;
	file >> frameRateLimit;
	file >> verticalSyncEnabled;
	file >> position.x >> position.y;

	file.close();

	std::cout << "title: " << title << '\n';
	std::cout << "width: " << width << '\n';
	std::cout << "height: " << height << '\n';
	std::cout << "FRL: " << frameRateLimit << '\n';
	std::cout << "verticalSyncEnabled: " << verticalSyncEnabled << '\n';
	std::cout << "pos: " << position.x << ' ' << position.y << '\n';

	m_window.setTitle(title);
	m_window.create(sf::VideoMode(width, height), title);
	m_window.setFramerateLimit(frameRateLimit);
	m_window.setVerticalSyncEnabled(verticalSyncEnabled);
	m_window.setPosition(position);
}

void App::loadData()
{
	std::cout << "Loading data...\n";

	m_trainInputs = Utils::MNISTdataLoader::readMnistImages(
		"handwritten digits data//train-images-idx3-ubyte"
	);
	auto trainLabels = Utils::MNISTdataLoader::readMnistLabels(
		"handwritten digits data//train-labels-idx1-ubyte"
	);

	m_testInputs = Utils::MNISTdataLoader::readMnistImages(
		"handwritten digits data//t10k-images-idx3-ubyte"
	);
	auto testLabels = Utils::MNISTdataLoader::readMnistLabels(
		"handwritten digits data//t10k-labels-idx1-ubyte"
	);

	std::cout << "\nThis is how 2 first data points look like:\n";

	Utils::MNISTdataLoader::showData(m_trainInputs, trainLabels, { 0U, 1U });

	Utils::MNISTdataLoader::preprocess(m_trainInputs);
	Utils::MNISTdataLoader::preprocess(m_testInputs);

	m_trainLabels = Utils::MNISTdataLoader::reorganizeLabels(trainLabels);
	m_testLabels = Utils::MNISTdataLoader::reorganizeLabels(testLabels);
}

void App::initNet()
{
	m_net = std::make_unique<NeuralNet>(NeuralNet({ 784U, 32U, 32U, 10U }, 1.0, 32U));
	m_net->save("XD kuriozum ale i tak rozkurwi� frajer�w etyk� pracy.ini");
}

void App::initDataPointRenderer()
{
	m_dataPointRenderer = std::make_unique<DataPointRenderer>(
		DataPointRenderer(
			sf::Vector2f(
				1000.0f,
				32.0f
			),
			sf::Vector2f(
				128.0f,
				128.0f
			),
			sf::Color::Magenta,
			4.0f,
			784U
		)
	);
}

void App::update()
{
	updateEvents();
	updateLearningProcess();
	updateRendering();
}

void App::render()
{
	m_window.clear();
	
	m_net->render(m_window);
	m_dataPointRenderer->render(m_window);
	
	m_window.display();
}

void App::updateEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void App::updateLearningProcess()
{
	m_net->trainingStep(
		m_trainInputs[m_trainingDataIdx],
		m_trainLabels[m_trainingDataIdx]
	);

	m_trainingDataIdx++;

	if (m_trainingDataIdx % 10'000 == 0)
	{
		std::cout << m_trainingDataIdx << '\n';
	}

	if (m_trainingDataIdx == m_trainInputs.size())
	{
		m_trainingDataIdx = 0U;

		m_net->saveWeightsAndBiases();

		std::cout << "Accuracy after " << m_epochIdx << " epoch: " << Utils::validateClassification(
			m_testInputs,
			m_testLabels,
			*m_net.get()
		) << '\n';

		exit(8);

		m_epochIdx++;

		std::string path = "after" + std::to_string(m_epochIdx) + "epoch.ini";
		std::cout << "so now lets save:\n";
		m_net->save(path);

		Utils::randomShuffle(m_trainInputs, m_trainLabels);
	}
}

void App::updateRendering()
{
	m_net->updateRendering();
	m_dataPointRenderer->updateRendering(m_trainInputs[m_trainingDataIdx]);
}
