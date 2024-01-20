from random import random
import math
class Perceptron(object):

	# Create a new Perceptron
	# 
	# Params:	bias -			arbitrarily chosen value that affects the overall output
	#					regardless of the inputs
	#
	#		synaptic_weights -	list of initial synaptic weights for this Perceptron

	def __init__(self, bias, synaptic_weights):
		self.bias = bias
		self.synaptic_weights = synaptic_weights


	# Activation function
	# Quantizes the induced local field
	#
	# Params:	z - the value of the induced local field
	#
	# Returns:	an integer that corresponds to one of the two possible output values (usually 0 or 1)
	
	def activation_function(self, z):
		if z >= 0:
			return 1
		else:
			return 0


	# Compute and return the weighted sum of all inputs (not including bias)
	#
	# Params:	inputs - a single input vector (which may contain multiple individual inputs)
	#
	# Returns:	a float value equal to the sum of each input multiplied by its
	#		corresponding synaptic weight

	def weighted_sum_inputs(self, inputs):
		total = 0
		for idx in range(len(self.synaptic_weights)):
			total += inputs[idx] * self.synaptic_weights[idx]
		return total


	# Compute the induced local field (the weighted sum of the inputs + the bias)
	#
	# Params:	inputs - a single input vector (which may contain multiple individual inputs)
	#
	# Returns:	the sum of the weighted inputs adjusted by the bias

	def induced_local_field(self, inputs):
		return self.weighted_sum_inputs(inputs) + self.bias


	# Predict the output for the specified input vector
	#
	# Params:	input_vector - a vector or row containing a collection of individual inputs
	#
	# Returns:	an integer value representing the final output, which must be one of the two
	#		possible output values (usually 0 or 1)

	def predict(self, input_vector):
		return self.activation_function(self.induced_local_field(input_vector))


	# Train this Perceptron
	#
	# Params:	training_set - 			a collection of input vectors that represents a subset of the entire dataset
	#
	#		learning_rate_parameter - 	the amount by which to adjust the synaptic weights following an
	#						incorrect prediction
	#
	#		number_of_epochs -		the number of times the entire training set is processed by the perceptron
	#
	# Returns:	no return value

	def modify_weights(self, input_vector, learning_rate_parameter, error):
		sqEr = error ** 2
		if error < 0:
			sqEr *= -1
		for j in range(len(input_vector) - 1):
			self.synaptic_weights[j] += learning_rate_parameter * input_vector[j] * sqEr
		self.bias += learning_rate_parameter * sqEr

	def train(self, training_set, learning_rate_parameter, number_of_epochs):
		for _ in range(number_of_epochs):
			for row in training_set:
				tOutput = self.predict(row)
				if tOutput != row[60]:
					self.modify_weights(row, learning_rate_parameter, row[60] - tOutput)
			# each epoch, very slightly reduce the learning rate by a factor of .9999
			learning_rate_parameter *= .9999

	# Test this Perceptron
	# Params:	test_set - the set of input vectors to be used to test the perceptron after it has been trained
	#
	# Returns:	a collection or list containing the actual output (i.e., prediction) for each input vector

	def test(self, test_set):
		output = []
		for idx in range(len(test_set)):
			output.append(self.predict(test_set[idx]))
		return output