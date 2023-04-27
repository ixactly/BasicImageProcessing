# BasicImageProcessing
(plan)
BasicImageProcessing is a C++ library for simple image processing tasks, such as blurring and edge detection.
for my study, i will not use OpenCV (only use image I/O)
## Features

* Gaussian blur
* Sobel edge detection
* Image resizing
* RGB to grayscale conversion

## Requirements

* OpenCV 3.0 or later

## Installation

1. Clone this repository.
2. Build the project using CMake.
3. Link the resulting library to your project.
4. Include the `BasicImageProcessing.h` header in your code.

## Usage

```c++
#include "BasicImageProcessing.h"

using namespace bip;

int main() {
  cv::Mat image = cv::imread("image.jpg");

  // Apply Gaussian blur
  image = blur(image, 5);

  // Convert to grayscale
  image = grayscale(image);

  // Detect edges using Sobel operator
  image = sobel(image);

  // Resize the image
  image = resize(image, 640, 480);

  // Save the processed image
  cv::imwrite("output.jpg", image);

  return 0;
}
```

## License
None.