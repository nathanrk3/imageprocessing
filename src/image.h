//
// Created by natek on 3/10/2024.
//

#ifndef PROJECT2_IMAGE_H
#define PROJECT2_IMAGE_H

#include <iostream>
#include <fstream>
#include <string>

struct Image{
    std::ifstream file_object;


    struct Header{
        char id_length;
        char color_map_type;
        char data_type_code;
        short color_map_origin;
        short color_map_length;
        char color_map_depth;
        short x_origin;
        short y_origin;
        short width;
        short height;
        char bits_per_pixel;
        char image_descriptor;

    };

    Header header;

    Image(const std::string& file_name);

    Image();



    unsigned char* pixel_array;

    void write_to(const std::string& file_name);

    Image* multiply(const Image& image_1, const Image& image_2);


    ~Image();

    Image* subtract(const Image& image_1);

    Image* screen(const Image& image_1);

    Image* add(const Image& image_1);

    Image* overlay(const Image& image_1);

    void scale_color(int i, int scale);

    void make_one_color(int j);

    void reverse();

    void add_color(int j, int num_to_add);
};

#endif //PROJECT2_IMAGE_ H


