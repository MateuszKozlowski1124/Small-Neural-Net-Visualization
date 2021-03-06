#pragma once

#include "SynapsesMatrix.h"

class Layer
{
public:
	virtual void setInput(const std::vector<Scalar>& input) = 0;
	virtual const std::vector<Scalar>& getInput() const = 0;
	
	virtual void propagateForward(
		const std::vector<Scalar>& inputVector,
		const SynapsesMatrix& inputSynapses
	) = 0;
	virtual void propagateForward(
		const Layer& previousLayer,
		const SynapsesMatrix& inputSynapses
	) = 0;

	virtual const std::vector<Scalar>& getOutput() = 0;

	virtual void calcDerivatives() = 0;

	virtual void calcErrors(const std::vector<Scalar>& desiredOutputs) = 0;

	virtual void propagateErrorsBack(
		const Layer& nextLayer,
		const SynapsesMatrix& outputSynapses
	) = 0;

	virtual const std::vector<Neuron>& getNeurons() const = 0;
	
	virtual void updateBiasesGradients() = 0;

	virtual unsigned getSize() const = 0;

	virtual void setBias(unsigned neuronIdx, const Scalar& bias) = 0;
	virtual const Scalar& getBias(unsigned neuronIdx) const = 0;
	virtual void resetBiasesGradients() = 0;

	virtual void updateRendering() = 0;
	virtual void render(sf::RenderTarget& target, bool bgIsRendered) const = 0;

	virtual void moveVertically(float offset) = 0;

	virtual const std::vector<sf::CircleShape>& getRenderedInputsCircles() const = 0;

	virtual unsigned getIdxOfFirstRenderedNetInput() const = 0;
	virtual unsigned getNumberOfRenderedNetInputs() const = 0;

	const sf::Vector2f& getPos() const;
	const sf::Vector2f& getRenderingSize() const;

	const sf::Color& getBgColor() const;

protected:
	sf::RectangleShape m_bg;
};
