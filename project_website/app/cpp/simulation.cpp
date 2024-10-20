#include <iostream>
#include <fstream>
#include "include/json.hpp"// Include the JSON library

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    // Check if the user provided the input and output files as arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file.json> <output_file.txt>" << std::endl;
        return 1;
    }

    // Open the input JSON file
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }

    // Parse the JSON input
    json input_data;
    try {
        input_file >> input_data;
    } catch (const json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return 1;
    }
    input_file.close();

    // DEBUG: Print to check if input was parsed correctly
    std::cout << "Input data parsed successfully." << std::endl;

    // Process the input (example: print the celestial bodies)
    std::ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not open output file " << argv[2] << std::endl;
        return 1;
    }

    // DEBUG: Print to check if the file is being opened
    std::cout << "Writing output to file: " << argv[2] << std::endl;

    for (auto& body : input_data["bodies"]) {
        try {
            std::string bodyType = body.at("bodyType");
            double x = body.at("x").get<double>();
            double y = body.at("y").get<double>();
            double z = body.at("z").get<double>();
            double mass = body.at("mass").get<double>();
            double radius = body.at("radius").get<double>();
            double rotationSpeed = body.at("rotationSpeed").get<double>();
            double theta = body.at("theta").get<double>();
            double phi = body.at("phi").get<double>();

            // Write data to the output file
            output_file << "Body Type: " << bodyType << "\n";
            output_file << "Position: (" << x << ", " << y << ", " << z << ")\n";
            output_file << "Mass: " << mass << ", Radius: " << radius << "\n";
            output_file << "Rotation Speed: " << rotationSpeed << "\n";
            output_file << "Rotation Axis (Theta, Phi): (" << theta << ", " << phi << ")\n";
            output_file << "-----------------------------------\n";

            // DEBUG: Print each body to ensure data is processed
            std::cout << "Processed body: " << bodyType << std::endl;
        } catch (const json::exception& e) {
            std::cerr << "JSON data type error: " << e.what() << std::endl;
        }
    }

    output_file.close();
    return 0;
}