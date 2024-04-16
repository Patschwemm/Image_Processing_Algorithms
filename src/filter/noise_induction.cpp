#include <opencv2/opencv.hpp>
#include <random>

cv::Mat noiseImgSaltPepper(cv::Mat& input, double noise_percent, bool inplace) {

	// If inplace is true, operate directly on the input matrix
	cv::Mat noiseMat = inplace ? input : input.clone();
	// Set up the random number generator
	std::random_device rand;
	// Mersenne Twister 19937 engine
	std::mt19937 gen(rand());
	// Define a distribution for integers between 0 and 255 for pixels, and 0 and noise_percent for noise
	std::uniform_real_distribution<double> rgb_distr(0.0, 255.0);
	std::uniform_real_distribution<double> prob(0, 1);

	// Loop over image pixels
	for (int y = 0; y < input.rows; ++y) {
		for (int x = 0; x < input.cols; ++x) {
			double rand_prob = prob(gen);
			// If random probability in noise percentage of sp noise
			if (rand_prob <= noise_percent){
				// Get random black/grey/white RGB pixel
				int salt_pepper_rgb = static_cast<int>(rgb_distr(gen));
				// Set current pixel to salt and pepper rgb value
				noiseMat.at<cv::Vec3b>(y, x) = cv::Vec3b(salt_pepper_rgb, salt_pepper_rgb, salt_pepper_rgb);
			}
		}
	}
			
	return noiseMat;
}
