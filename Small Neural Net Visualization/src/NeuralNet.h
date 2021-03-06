#pragma once

#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"
#include "DesiredOutputsRenderer.h"

class NeuralNet
{
public:
	NeuralNet(
		const std::vector<unsigned>& topology,
		const Scalar& learningRate,
		unsigned miniBatchSize,
		const sf::Vector2f& pos,
		const sf::Vector2f& size,
		const sf::Color& bgColor,
		const sf::Color& layersBgColor,
		const sf::Color& desiredOutputsBgColor,
		const sf::Color& baseNeuronsColor,
		bool bgIsRendered,
		bool layersBgAreRendered
	);
	NeuralNet(const std::string& filePath);

	const sf::Vector2f& getPos() const;
	const sf::Vector2f& getSize() const;

	void saveToFile(const std::string& filePath);
	void loadFromFile(const std::string& filePath);

	const std::vector<Scalar>& getOutput() const;
	const std::vector<Scalar>& predict(const std::vector<Scalar>& input);
	
	void trainingStep(
		const std::vector<Scalar>& input,
		const std::vector<Scalar>& desiredOutput
	);

	void updateRendering(const std::vector<Scalar>& desiredOutput);
	void render(sf::RenderTarget& target);

	bool isBgRendered() const;
	void hideBg();
	void showBg();

	bool areLayersBgRendered() const;
	void hideLayersBg();
	void showLayersBg();

private:
	void initLayers(
		const std::vector<unsigned>& topology,
		const sf::Vector2f& pos, 
		const sf::Vector2f& size,
		const sf::Color& layersBgColor,
		const sf::Color& baseNeuronsColor
	);
	void initSynapses(const std::vector<unsigned>& topology);
	void initBg(
		const sf::Vector2f& pos,
		const sf::Vector2f& size,
		const sf::Color& bgColor
	);
	void initDesiredOutputsRenderer(
		const std::vector<unsigned>& topology,
		const sf::Vector2f& pos,
		const sf::Vector2f& size,
		const sf::Color& desiredOutputsBgColor,
		const sf::Color& baseColorOfDesiredOutputsCircles
	);

	static float calcNeuronDiameter(
		const std::vector<unsigned>& topology,
		float netHeight
	);
	static unsigned getBiggestNonInputLayerSize(const std::vector<unsigned>& topology);
	static float calcSpaceBetweenLayers(
		const std::vector<unsigned>& topology,
		const sf::Vector2f& size
	);

	void alignNonInputLayersVertically(const sf::Vector2f& size);

	void propagateForward(const std::vector<Scalar>& input);

	void calcDerivatives();
	void propagateErrorsBack();
	
	void updateGradients();
	void updateWeightsGradients();
	void updateBiasesGradients();

	void updateWeights();
	void updateBiases();

	void resetGradients();
	void resetWeightsGradients();
	void resetBiasesGradients();

	Scalar getBiggestAbsValOfWeight() const;

	unsigned m_trainingStep;

	Scalar m_learningRate;
	unsigned m_miniBatchSize;
	
	bool m_bgIsRendered;
	bool m_layersBgAreRendered;

	sf::RectangleShape m_bg;

	std::vector<std::unique_ptr<Layer>> m_layers;
	std::vector<SynapsesMatrix> m_synapses;

	std::unique_ptr<DesiredOutputsRenderer> m_desiredOutputsRenderer;
};
