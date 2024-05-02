// File: CS112_A3_Part2B_S21-S22_20230078_20230713_20230735.cpp
// Purpose: Simple image processing application that allows users to load, apply various filters (grayscale conversion, invert, darken/lighten, rotate, black and white, flip, resize, crop, blur, adding frame, merge, edges detect, purple, infrared, sunlight), and save images.
// Authors: Eyad Yossri (20230078) (S22) - Mohamed Abdulmajeed (20230713) (S21) - Mohamed Elmugtaba (20230735) (S21)
// ID1: 20230078 – Filter 1 (Grayscale) & Filter 4 (Merge) & Filter 7 (Darken and Lighten) & Filter 10 (Edges Detect) & Filter 16 (Purple) & all menus in the program
// ID3: 20230713 – Filter 2 (Black and White) & Filter 5 (Flip) & Filter 8 (Crop) & Filter 11 (Resize) & Filter 13 (Sunlight)
// ID2: 20230735 – Filter 3 (Invert Image) & Filter 6 (Rotate Image) & Filter 9 (Adding Frame) & Filter 12 (Blur) & Filter 17 (Infrared)

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "Image_Class.h"

using namespace std;

// Function prototypes
void loadImage(string &currentImage);
void saveImage(Image image, string &currentImage);
void displayMainMenu();
void displayFilterMenu();
Image processFilterMenuChoice(string &currentImage, char choice);
void processMainMenuChoice(string &currentImage, Image &filteredImage, char choice);
void filterGrayscale(Image &image);
void filterInvert(Image &image);
void filterDarkenLighten(Image &image);
Image filterRotate(Image &image);
void filterBlackWhite(Image &image);
void filterFlip(Image &image);
void filterResize(Image &image);
void filterCrop(Image &image);
void filterBlur(Image &image);
void addFrame(Image &image);
void frame(Image& image, int width, int colors[3]);
void designFrame(Image& image, int width, int colors[3]);
void resizeMerge(Image &image1, Image &image2);
void filterMerge(Image &image1, Image &image2);
void edgeDetect(Image &image);
void filterPurple(Image &image);
void infrared(Image &image);
void sunlight(Image &image);



int main() {
    char choice;
    string currentImage;
    Image filteredImage;

    do {
        displayMainMenu(); // Display the main menu
        cin >> choice; // Get user's choice
        processMainMenuChoice(currentImage, filteredImage, choice); // Process user's choice
    } while (choice != 'E' && choice != 'e'); // Exit loop when 'E' or 'e' is entered

    return 0;
}

// Function to load an image
void loadImage(string &currentImage) {
    bool validFile = false;

    do {
        cout << "Enter the name of the file to load: ";
        cin >> currentImage;

        // Check if the file exists
        ifstream file(currentImage);
        if (file.good()) {
            // Check if the filename has a valid extension
            string extension = currentImage.substr(currentImage.find_last_of(".") + 1);
            if (extension != "jpg" && extension != "jpeg" && extension != "png" && extension != "bmp" && extension != "tga") {
                cout << "Error: Invalid file extension. Please enter a filename with .jpg, .jpeg, .png, .bmp, or .tga extension.\n";
            } else {
                file.close();
                validFile = true;
            }
        } else {
            cout << "Error: File '" << currentImage << "' does not exist.\n";
        }
    } while (!validFile);
}

// Function to save an image
void saveImage(Image image, string &currentImage) {
    string imageNewName;

    cout << "\nEnter new image name to store or Enter original image name to store at the same file";
    cout << "\n& specify extension .jpg, .png, .bmp, .tga :";

    cin >> imageNewName;

    // Check if the new image name is valid
    bool validName = false;
    do {
        string extension = imageNewName.substr(imageNewName.find_last_of(".") + 1);
        if (extension != "jpg" && extension != "jpeg" && extension != "png" && extension != "bmp" && extension != "tga") {
            cout << "Error: Invalid file extension. Please enter a filename with .jpg, .jpeg, .png, .bmp, or .tga extension: ";
            cin >> imageNewName;
        } else {
            ofstream file(imageNewName);
            if (file) {
                validName = true;
                file.close();
            } else {
                cout << "Error: Invalid filename. Please enter a valid filename: ";
                cin >> imageNewName;
            }
        }
    } while (!validName);

    image.saveImage(imageNewName); // Save the filtered image
    system(imageNewName.c_str());

    // Update the currentImage variable to the newly saved image
    currentImage = imageNewName;
}

// Function to display the main menu
void displayMainMenu() {
    cout << "\n** MAIN MENU:\n";
    cout << "1. Load an image\n";
    cout << "2. Save the image\n";
    cout << "E. Exit\n";
    cout << "Enter your choice: ";
}

// Function to display the filter menu
void displayFilterMenu() {
    cout << "\n** FILTER MENU:\n";
    cout << "A. Grayscale Conversion\n";
    cout << "B. Invert\n";
    cout << "C. Darken/Lighten\n";
    cout << "D. Rotate\n";
    cout << "E. Black and White\n";
    cout << "F. Flip \n";
    cout << "G. Resize \n";
    cout << "H. Crop \n";
    cout << "I. Blur \n";
    cout << "J. Merge \n";
    cout << "K. Detect Edges \n";
    cout << "L. Adding Frame \n";
    cout << "M. Purple \n";
    cout << "N. Infrared \n";
    cout << "O. Sunlight \n";
    cout << "P. Back to Main Menu <--\n";
    cout << "Enter your choice: ";
}

// Function to process user's choice in the filter menu
Image processFilterMenuChoice(string &currentImage, char choice) {
    switch (choice) {
        case 'A':
        case 'a':
            // Apply Grayscale Conversion filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterGrayscale(loadedImage); // Apply grayscale filter
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'B':
        case 'b':
            // Apply Invert filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterInvert(loadedImage); // Apply invert filter
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'C':
        case 'c':
            // Apply Darken/Lighten filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterDarkenLighten(loadedImage); // Apply darken/lighten filter
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'D':
        case 'd':
            // Apply Rotate filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                return filterRotate(loadedImage); // Return the rotated image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'E':
        case 'e':
            // Apply Black and White filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterBlackWhite(loadedImage); // Apply black and white filter
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'F':
        case 'f':
            // Apply Flip filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterFlip(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'G':
        case 'g':
            // Apply Resize filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterResize(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'H':
        case 'h':
            // Apply Crop filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterCrop(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'I':
        case 'i':
            // Apply Blur filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterBlur(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'J':
        case 'j':
            // Apply Merge filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                string second_filename;
                cout << "Enter the name of the second file to Merge:";
                cin >> second_filename;
                Image image2(second_filename);
                filterMerge(loadedImage,image2);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'K':
        case 'k':
            // Apply Edge Detect filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                edgeDetect(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'L':
        case 'l':
            // Apply Adding Frame filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                addFrame(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'M':
        case 'm':
            // Apply Purple filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                filterPurple(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'N':
        case 'n':
            // Apply Infrared filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                infrared(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'O':
        case 'o':
            // Apply Sunlight filter
            if (!currentImage.empty()) {
                Image loadedImage(currentImage);
                sunlight(loadedImage);
                return loadedImage; // Return the filtered image
            } else {
                cout << "Error: No image loaded. Please load an image first.\n";
            }
            break;
        case 'P':
        case 'p':
            // Back to Main Menu
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
    return {}; // Return an empty image if no valid option is chosen
}

// Function to process user's choice in the main menu
void processMainMenuChoice(string &currentImage, Image &filteredImage, char choice) {
    switch (choice) {
        case '1':
            loadImage(currentImage); // Load an image
            if (!currentImage.empty()) {
                // Load successful, now display filter menu
                char filterChoice;
                do {
                    displayFilterMenu(); // Display the filter menu
                    cin >> filterChoice; // Get user's filter choice
                    if (filterChoice != 'P' && filterChoice != 'p')
                        filteredImage = processFilterMenuChoice(currentImage, filterChoice); // Process the filter choice
                } while (filterChoice != 'P' && filterChoice != 'p'); // Back to main menu when 'P' or 'p'  is entered
            }
            break;
        case '2':
            if (!currentImage.empty())
                saveImage(filteredImage, currentImage); // Save the image
            else
                cout << "Error: No image loaded. Please load an image first.\n";
            break;
        case 'E':
        case 'e':
            // Ask user if they want to save before exit
            cout << "Do you want to save before exit? (Y/N): ";
            char saveChoice;
            cin >> saveChoice;
            if (saveChoice == 'Y' || saveChoice == 'y')
                saveImage(filteredImage, currentImage);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}

// Function to apply grayscale filter
void filterGrayscale(Image &image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            // Calculate the average value across all color channels
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }

            avg /= image.channels; // Correctly calculate the average

            // Set the grayscale value for all channels
            for (int k = 0; k < image.channels; ++k) {
                image.setPixel(i, j, k, avg);
            }
        }
    }
    cout << "\n*< Grayscale Filter is applied >*\n";
}

// Function to apply invert filter
void filterInvert(Image &image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    cout << "\n*< Invert Filter is applied >*\n";
}

// Function to apply darken/lighten filter
void filterDarkenLighten(Image &image) {
    string filterChoose;
    cout << "\nChoose an option:\n";
    cout << "1. Darken Filter\n";
    cout << "2. Lighten Filter\n";
    cout << "Enter your option (1/2):";
    cin >> filterChoose;

    if (filterChoose == "1") {
        int totalPixels = image.width * image.height * image.channels;
        for (int i = 0; i < totalPixels; ++i) {
            image.imageData[i] /= 2;
        }
        cout << "\n*< Darken Filter is applied >*\n";
    } else if (filterChoose == "2") {
        int totalPixels = image.width * image.height * image.channels;
        for (int i = 0; i < totalPixels; ++i) {
            int newValue = image.imageData[i] + 50;
            image.imageData[i] = newValue > 255 ? 255 : static_cast<unsigned char>(newValue);
        }
        cout << "\n*< Lighten Filter is applied >*\n";
    }
}

// Function to apply rotate filter
Image filterRotate(Image &image) {
    int choose;
    cout << "in which rotation you want to rotate the photo (90, 180, 270): ";
    cin >> choose;
    Image rotatedImage;

    if (choose == 90) {
        Image ron(image.height, image.width);
        for (int i = 0; i < image.height; ++i) {
            for (int j = 0; j < image.width; ++j) {
                int newX = i;
                int newY = image.width - 1 - j;
                for (int k = 0; k < 3; ++k) {
                    ron.setPixel(newX, newY, k, image.getPixel(j, i, k));
                }
            }
        }
        cout << "\n*< Rotate(90) Filter is applied >*\n";
        rotatedImage = ron;
    } else if (choose == 180) {
        Image ron2(image.width, image.height);
        for (int i = 0; i < image.height; ++i) {
            for (int j = 0; j < image.width; ++j) {
                int newX = image.width - 1 - j;
                int newY = image.height - 1 - i;
                for (int k = 0; k < 3; ++k) {
                    ron2.setPixel(newX, newY, k, image.getPixel(j, i, k));
                }
            }
        }
        cout << "\n*< Rotate(180) Filter is applied >*\n";
        rotatedImage = ron2;
    } else if (choose == 270) {
        Image ron(image.height, image.width);
        for (int i = 0; i < image.height; ++i) {
            for (int j = 0; j < image.width; ++j) {
                int newX = image.height - 1 - i;
                int newY = j;
                for (int k = 0; k < 3; ++k) {
                    ron.setPixel(newX, newY, k, image.getPixel(j, i, k));
                }
            }
        }
        cout << "\n*< Rotate(270) Filter is applied >*\n";
        rotatedImage = ron;
    } else {
        cout << "Invalid choice ";
    }

    return rotatedImage;
}

// Function to apply black and white filter
void filterBlackWhite(Image &image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }

            avg = avg / 3;

            if (avg <= 127) {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            } else {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    cout << "\n*< Black & White Filter is applied >*\n";
}

// Function to apply Purple filter
void filterPurple(Image &image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int green = image(i, j, 1);
            unsigned int newGreen = green * 0.7;

            image(i, j, 1) = newGreen;

        }
    }
    cout << "\n*< Purple Filter is applied >*\n";
}

// Function to apply Flip filter
void filterFlip(Image &image) {
    string filterChoose;
    cout << "\nChoose an option:\n";
    cout << "1. Flip Horizontal\n";
    cout << "2. Flip Vertical\n";
    cout << "Enter your option (1/2):";
    cin >> filterChoose;

    if (filterChoose == "1") {
        int width = image.width;
        int height = image.height;
        Image flippedImage(width, height);

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    flippedImage.setPixel(i, j, k, image.getPixel(width - 1 - i, j, k));
                }
            }
        }

        // Update the original image with the flipped image
        image = flippedImage;
        cout << "\n*< Horizontal Flip Filter is applied >*\n";

    } else if (filterChoose == "2") {
        int width = image.width;
        int height = image.height;
        Image flippedImage(width, height);

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    flippedImage.setPixel(i, j, k, image.getPixel(i, height - 1 - j, k));
                }
            }
        }

        // Update the original image with the flipped image
        image = flippedImage;
        cout << "\n*< Vertical Flip Filter is applied >*\n";
    }

}

// Function to apply Resize filter
void filterResize(Image &image){
    double width , height ;
    cout << "image width : " << image.width << '\n' ;
    cout << "image height : " << image.height << '\n' ;
    cout << "what is the ratio you want to resize to ? : " << endl ;
    cout << "Enter the height : " ;
    cin >> height;
    cout<< "Enter the width : " ;
    cin >> width ;
    double widthRatio = (image.width) / width ;
    double heightRatio = (image.height) / height ;
    Image image2(width, height);
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for(int k = 0 ; k < 3 ; k++ ){
                unsigned int value ;
                value = image(round(i*widthRatio), round(j*heightRatio),k);
                image2(i,j,k) = value  ;
            }
        }
    }
    image = image2;
    cout << "\n*< Resize Filter is applied >*\n";

}

// Function to apply Crop filter
void filterCrop(Image &image){
    int startingWidth , startingHeight ,width , height ;
    cout << "The width of the photo : " << image.width << endl ;
    cout << "The height of the photo : " << image.height << endl ;
    cout << "Enter the starting pixel points ? " << '\n';
    cout << "Enter the width start from : " ;
    cin >> startingWidth ;
    cout << "Enter the height start from : " ;
    cin >> startingHeight ;
    cout << "Enter the dimensions to crop to ? " << '\n' ;
    cout << "Enter the width to crop to : " ;
    cin >> width ;
    cout << "Enter the height to crop to : " ;
    cin >> height ;
    Image image2(width,height) ;
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image2(i,j,k) = image((i+startingWidth) , (j + startingHeight),k) ;
            }
        }
    }

    image = image2;
    cout << "\n*< Crop Filter is applied >*\n";
}

// Function to apply Blur filter
void filterBlur(Image &image){

    Image blurImage(image.width, image.height);
    // Apply box blur filter
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            for (int c = 0; c < 3; ++c) {
                unsigned int sum = 0;
                int count = 0;
                for (int j = -5; j <= 5; j++) {
                    for (int i = -5; i <= 5; i++) {
                        // Calculate the coordinates of the pixel within the image
                        int pixelx = x + i;
                        int pixely = y + j;
                        // Check if the calculated pixel coordinates are within the image bounds
                        if (pixelx >= 0 && pixelx < image.width && pixely >= 0 && pixely < image.height) {
                            sum += image.getPixel(pixelx, pixely, c);
                            count++;
                        }
                    }
                }
                float avg = static_cast<float>(sum) / count; // Calculate the average
                blurImage.setPixel(x, y, c, static_cast<int>(avg)); // Set the blurred pixel value
            }
        }
    }
    image = blurImage;
    cout << "\n*< Blur Filter is applied >*\n";
}

// Function to apply Resize to images before Merge filter
void resizeMerge(Image &image1, Image &image2) {
    // Determine the maximum width and height among the two images
    double maxWidth = max(image1.width, image2.width);
    double maxHeight = max(image1.height, image2.height);

    // Calculate the width and height ratios for each image
    double widthRatio1 = image1.width / maxWidth;
    double heightRatio1 = image1.height / maxHeight;
    double widthRatio2 = image2.width / maxWidth;
    double heightRatio2 = image2.height / maxHeight;

    // Create a new image with the largest width and height
    Image resizedImage1(maxWidth, maxHeight);
    Image resizedImage2(maxWidth, maxHeight);

    // Resize image1
    for (int i = 0; i < resizedImage1.width; ++i) {
        for (int j = 0; j < resizedImage1.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                unsigned int value = image1(round(i * widthRatio1), round(j * heightRatio1), k);
                resizedImage1(i, j, k) = value;
            }
        }
    }

    // Resize image2
    for (int i = 0; i < resizedImage2.width; ++i) {
        for (int j = 0; j < resizedImage2.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                unsigned int value = image2(round(i * widthRatio2), round(j * heightRatio2), k);
                resizedImage2(i, j, k) = value;
            }
        }
    }

    // Update the original images with the resized images
    image1 = resizedImage1;
    image2 = resizedImage2;
}

// Function to apply Merge filter
void filterMerge(Image &image1, Image &image2) {
    string filterChoose;
    cout << "\nChoose an option:\n";
    cout << "1. Resize both images to the biggest height and the biggest width and then Merge\n";
    cout << "2. Merge the common area of the smaller width and the smaller height.\n";
    cout << "Enter your option (1/2):";
    cin >> filterChoose;

    if (filterChoose == "1") {
        resizeMerge(image1, image2);
        double newWidth = max(image1.width, image2.width);
        double newHeight = max(image1.height, image2.height);

        // Merge images
        Image mergedImage(newWidth, newHeight);

        // Perform merging operation here, for example, taking the average of pixel values
        for (int j = 0; j < newHeight; ++j) {
            for (int i = 0; i < newWidth; ++i) {
                for (int k = 0; k < mergedImage.channels; ++k) {
                    // Taking the average of pixel values
                    mergedImage(i, j, k) = (image2(i, j, k) + image1(i, j, k)) / 2;
                }
            }
        }
        image1 = mergedImage;
        cout << "\n*< Merge Filter is applied >*\n";

    } else if (filterChoose == "2") {
        int newWidth = min(image1.width, image2.width);
        int newHeight = min(image1.height, image2.height);

        // Merge images
        Image mergedImage(newWidth, newHeight);

        // Perform merging operation here, for example, taking the average of pixel values
        for (int j = 0; j < newHeight; ++j) {
            for (int i = 0; i < newWidth; ++i) {
                for (int k = 0; k < mergedImage.channels; ++k) {
                    // Taking the average of pixel values
                    mergedImage(i, j, k) = (image2(i, j, k) + image1(i, j, k)) / 2;
                }
            }
        }
        image1 = mergedImage;
        cout << "\n*< Merge Filter is applied >*\n";
    }
}

// Function to apply Edge Detect filter
void edgeDetect(Image &image) {
    // Define the Sobel operator kernels for horizontal and vertical gradients
    int kernelX[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int kernelY[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
    Image outputImage (image.width,image.height);

    // Iterate over the image pixels to apply the Sobel operator
    for (int y = 1; y < image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            // Compute the gradient in the x direction
            int gradientX = 0;
            for (int j = -1; j <= 1; ++j) {
                for (int i = -1; i <= 1; ++i) {
                    gradientX += kernelX[j + 1][i + 1] * image(x + i, y + j, 0);
                }
            }

            // Compute the gradient in the y direction
            int gradientY = 0;
            for (int j = -1; j <= 1; ++j) {
                for (int i = -1; i <= 1; ++i) {
                    gradientY += kernelY[j + 1][i + 1] * image(x + i, y + j, 0);
                }
            }

            // Compute the magnitude of the gradient
            int magnitude = sqrt(gradientX * gradientX + gradientY * gradientY);

            // Invert the intensity value to represent edges with black
            magnitude = 255 - magnitude;

            // Threshold the intensity to convert it to black or white
            int threshold = 100; // Adjust this threshold value as needed
            if (magnitude < threshold) {
                magnitude = 0; // Set to black
            } else {
                magnitude = 255; // Set to white
            }
            // Set the magnitude as the intensity of the output pixel
            outputImage(x, y, 0) = magnitude;
            outputImage(x, y, 1) = magnitude;
            outputImage(x, y, 2) = magnitude;
        }
    }
    image = outputImage;
    cout << "\n*< Detect Edges Filter is applied >*\n";
}

// Function to apply Infrared filter
void infrared(Image &image) {
    int aver;
    for (int i = 0; i < image.width ; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; k++) {
                aver += image(i, j, k);
            }

            aver = aver / 3;
            if (aver>=130){
                image(i,j,0)=255;
                image(i,j,1)=255- aver ;
                image(i,j,2)=255 - aver;
            }
            else{
                image(i,j,0)=255-(aver/5);
                image(i,j,1)=255-aver;
                image(i,j,2)=255-aver;
            }
            aver = 0;
        }
    }
    cout << "\n*< Infrared Filter is applied >*\n";
}

// Function to apply Sunlight filter
void sunlight(Image &image) {
    for (int i = 0; i < image.width ; ++i) {
        for (int j = 0; j < image.height; ++j) {
            if(image(i,j,0) + 15 <= 255) image(i,j,0) += 15 ;
            else image(i,j,0) = 255 ;
            if(image(i,j,1) + 40 <= 255) image(i,j,1) += 40 ;
            else image(i,j,1) = 255 ;
            if(image(i,j,2) - 15 >= 0) image(i,j,2) -= 15 ;
            else image(i,j,2) = 0 ;
        }
    }
    cout << "\n*< Sunlight Filter is applied >*\n";
}

// Function to apply frame function before adding frame filter
void frame(Image& image, int width, int colors[3]) {
    for (int j = 0; j < image.height; j++) {
        for (int i = 0; i < image.width; i++) {
            if (i < width || j < width || i >= image.width - width || j >= image.height - width) {
                for (int k = 0; k < 3; k++) {
                    image.setPixel(i, j, k, colors[k]);
                }
            }
        }
    }
}

// Function to apply designed frame before adding frame filter
void designFrame(Image& image, int width, int colors[3]) {
    for (int j = 0; j < image.height; j++) {
        for (int i = 0; i < image.width; i++) {
            if ((i >= 4 && i <= 8) || (j >= 4 && j <= 8) || (i >= image.width - 8 && i <= image.width - 4) || (j >= image.height - 8 && j <= image.height - 4)) {
                for (int k = 0; k < 3; k++) {
                    image.setPixel(i, j, k, colors[k]);
                }
            }
            if ((i >= 12 && i <= 16) || (j >= 12 && j <= 16) || (i >= image.width - 16 && i <= image.width - 12) || (j >= image.height - 16 && j <= image.height - 12)) {
                for (int k = 0; k < 3; k++) {
                    image.setPixel(i, j, k, colors[k]);
                }
            }
            if ((i >= 20 && i <= 24) || (j >= 20 && j <= 24) || (i >=image.width - 24 && i <= image.width - 20) || (j >= image.height - 24 && j <= image.height - 20)) {
                for (int k = 0; k < 3; k++) {
                    image.setPixel(i, j, k, colors[k]);
                }
            }
        }
    }
}

// Function to apply Adding Frame filter
void addFrame(Image &image){
    cout << "Choose an option:\n1. Frame\n2. Design Frame" << endl;
    int option;
    char choice; // Changed to char type
    cin >> option;
    int width = (image.width) * 0.016;
    switch (option) {
        case 1: {
            cout << "Choose a color for the designFrame (1-red, 2-green, 3-blue): " << endl;
            int chosenColor;
            cin >> chosenColor;
            if (chosenColor == 1) {
                int color[3] = {255, 0, 0};
                frame(image, width, color);
            } else if (chosenColor == 2) {
                int color[3] = {0, 255, 0};
                frame(image, width, color);
            } else if (chosenColor == 3) {
                int color[3] = {0, 0, 255};
                frame(image, width, color);
            } else {
                cout << "Invalid color choice. Defaulting to white." << endl;
                int color[3] = {255, 255, 255};
                frame(image, width, color);
            }
            break;
        }
        case 2: {
            cout << "Choose a color for the frame (1-red, 2-green, 3-blue): " << endl;
            int chosenColor;
            cin >> chosenColor;

            if (chosenColor == 1) {
                int color[3] = {255, 0, 0};
                designFrame(image, width, color);
            } else if (chosenColor == 2) {
                int color[3] = {0, 255, 0};
                designFrame(image, width, color);
            } else if (chosenColor == 3) {
                int color[3] = {0, 0, 255};
                designFrame(image, width, color);
            } else {
                cout << "Invalid color choice. Defaulting to white." << endl;
                int color[3] = {255, 255, 255};
                designFrame(image, width, color);
            }
            break;
        }
        default:
            cout << "Invalid option. Defaulting to red frame." << endl;
            int color[3] = {255, 0, 0};
            frame(image, width, color);
            break;
    }
    cout << "\n*< Adding Frame Filter is applied >*\n";
}





