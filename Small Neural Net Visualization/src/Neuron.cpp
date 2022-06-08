#include "Neuron.h"

Neuron::Neuron()
	: m_val(0.0),
	  m_bias(0.0),
	  m_actVal(0.0),
	  m_derivative(0.0),
	  m_lossDerivativeWithRespectToActFunc(0.0),
	  m_biasGradient(0.0)
{

}

void Neuron::setVal(const Scalar& val)
{
	m_val = val;
}

void Neuron::activate()
{
	Scalar biasedVal = m_val + m_bias;

	//std::cout << "val: " << m_val << ",bias: " << m_bias << '\n';

	m_actVal = 1.0 / (1.0 + exp(-biasedVal));

	//std::cout << "act: " << m_actVal << '\n';
}

const Scalar& Neuron::getActVal() const
{
	return m_actVal;
}

void Neuron::calcDerivative()
{
	m_derivative = m_actVal * (1.0 - m_actVal);
}

void Neuron::calcLossDerivativeWithRespectToActFunc(const Scalar& desiredOutput)
{
	m_lossDerivativeWithRespectToActFunc = m_actVal - desiredOutput;
}

void Neuron::calcLossDerivativeWithRespectToActFunc(
	unsigned idxInLayer, 
	const std::vector<Neuron>& nextLayerNeurons, 
	const std::vector<std::vector<Synapse>>& outputSynapses)
{
	m_lossDerivativeWithRespectToActFunc = 0.0;

	for (int n = 0; n < nextLayerNeurons.size(); n++)
	{
		m_lossDerivativeWithRespectToActFunc +=
			outputSynapses[n][idxInLayer].getWeight() *
			nextLayerNeurons[n].getDerivative() *
			nextLayerNeurons[n].getLossDerivativeWithRespectToActFunc();
	}
}

const Scalar& Neuron::getDerivative() const
{
	return m_derivative;
}

const Scalar& Neuron::getLossDerivativeWithRespectToActFunc() const
{
	return m_lossDerivativeWithRespectToActFunc;
}

void Neuron::setBias(const Scalar& bias)
{
	m_bias = bias;
}

const Scalar& Neuron::getBias() const
{
	return m_bias;
}

const Scalar& Neuron::getBiasGradient() const
{
	return m_biasGradient;
}

void Neuron::updateBiasGradient()
{
	/*std::cout
		<< "Hi I'm neuron and: "
		<< m_derivative << "*" << m_lossDerivativeWithRespectToActFunc << "="
		<< m_derivative * m_lossDerivativeWithRespectToActFunc << '\n';*/

	m_biasGradient += m_derivative * m_lossDerivativeWithRespectToActFunc;
}

void Neuron::resetBiasGradient()
{
	m_biasGradient = 0.0;
}
