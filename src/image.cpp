
// Created by natek on 3/10/2024.

#include "image.h"

void Image::write_to(const std::string& file_name){
    std::ofstream file_object(file_name, std::ios_base::binary);
    if(file_object.is_open()){
        std::cout << "Opened" << std::endl;
    }
    else{
        std::cout << "Did Not Opened" << std::endl;

    }

    file_object.write(&(header.id_length), 1);
    file_object.write(&(header.color_map_type), 1);
    file_object.write(&header.data_type_code, 1);
    file_object.write(reinterpret_cast<char*>(&header.color_map_origin), 2);
    file_object.write(reinterpret_cast<char*>(&header.color_map_length), 2);
    file_object.write(&header.color_map_depth, 1);
    file_object.write(reinterpret_cast<char*>(&header.x_origin), 2);
    file_object.write(reinterpret_cast<char*>(&header.y_origin), 2);
    file_object.write(reinterpret_cast<char*>(&header.width), 2);
    file_object.write(reinterpret_cast<char*>(&header.height), 2);
    file_object.write(&header.bits_per_pixel, 1);
    file_object.write(&header.image_descriptor, 1);
    file_object.write(reinterpret_cast<char*>(pixel_array), 3 * header.width * header.height);
    file_object.close();


}

Image* Image::multiply(const Image& image_1, const Image& image_2){
    Image* image_3 = new Image;
    image_3->header = image_1.header;
    image_3->pixel_array = new unsigned char[image_3->header.width* image_3->header.height * 3];
    for(int i = 0; i < image_3->header.width* image_3->header.height * 3; i++){
        image_3->pixel_array[i] = static_cast<unsigned char>(255 * (float(image_2.pixel_array[i]) / 255) * (float(image_1.pixel_array[i]) / 255) + .5f);
    }
    return image_3;
}
Image::Image(const std::string& file_name) {
    file_object.open(file_name, std::ios_base::binary);


    file_object.read(&(header.id_length), 1);
    file_object.read(&(header.color_map_type), 1);
    file_object.read(&header.data_type_code, 1);
    file_object.read(reinterpret_cast<char*>(&header.color_map_origin), 2);
    file_object.read(reinterpret_cast<char*>(&header.color_map_length), 2);
    file_object.read(&header.color_map_depth, 1);
    file_object.read(reinterpret_cast<char*>(&header.x_origin), 2);
    file_object.read(reinterpret_cast<char*>(&header.y_origin), 2);
    file_object.read(reinterpret_cast<char*>(&header.width), 2);
    file_object.read(reinterpret_cast<char*>(&header.height), 2);
    file_object.read(&header.bits_per_pixel, 1);
    file_object.read(&header.image_descriptor, 1);

    pixel_array = new unsigned char[3 * header.width * header.height];
    file_object.read(reinterpret_cast<char*>(pixel_array), 3 *header.width * header.height);


}



Image::Image(){
    header.id_length = 0;
    header.color_map_type = 0;
    header.data_type_code = 0;
    header.color_map_origin = 0;
    header.color_map_length = 0;
    header.color_map_depth = 0;
    header.x_origin = 0;
    header.y_origin = 0;
    header.width = 0;
    header.height = 0;
    header.bits_per_pixel = 0;
    header.image_descriptor = 0;

    pixel_array = nullptr;
}

Image::~Image(){
    if(pixel_array != nullptr){
        delete[] pixel_array;
    }
}

Image* Image::subtract(const Image& image_1){

    Image* image_3 = new Image;
    image_3->header = image_1.header;
    image_3->pixel_array = new unsigned char[image_3->header.width* image_3->header.height * 3];
    for(int i = 0; i < image_3->header.width* image_3->header.height * 3; i++){
        int check_for_negative = this->pixel_array[i] - image_1.pixel_array[i];
        if(check_for_negative > 0){
            image_3->pixel_array[i] = check_for_negative;
        }
        else{
            image_3->pixel_array[i] = 0;
        }
    }
    return image_3;
}

Image* Image::screen(const Image& image_1){
    Image* image_3 = new Image;
    image_3->header = image_1.header;
    image_3->pixel_array = new unsigned char[image_3->header.width* image_3->header.height * 3];
    for(int i = 0; i < image_3->header.width* image_3->header.height * 3; i++){
        float img_1 = float(image_1.pixel_array[i]) / 255;
        float img = float(this->pixel_array[i]) / 255;
        float img_3 = 1 - ((1 - img_1) * (1 - img));
        image_3->pixel_array[i] = static_cast<unsigned char>(255 * img_3 + .5f);
    }
    return image_3;

}

Image* Image::add(const Image& image_1){
    Image* image_3 = new Image;
    image_3->header = image_1.header;
    image_3->pixel_array = new unsigned char[image_3->header.width* image_3->header.height * 3];
    for(int i = 0; i < image_3->header.width* image_3->header.height * 3; i++){
        int check = this->pixel_array[i] + image_1.pixel_array[i];
        if(check > 255){
            image_3->pixel_array[i] = check;
        }
        else{
            image_3->pixel_array[i] = 255;
        }
    }
    return image_3;
}


Image* Image::overlay(const Image &image_1){
    Image* image_3 = new Image;
    image_3->header = image_1.header;
    image_3->pixel_array = new unsigned char[image_3->header.width* image_3->header.height * 3];
    for(int i = 0; i < image_3->header.width* image_3->header.height * 3; i++){
        float img = float(this->pixel_array[i]) / 255;
        float img_1 = float(image_1.pixel_array[i]) / 255;
        if(img_1 <= .5){
            float result = 2 * img_1 * img;
            image_3->pixel_array[i] = static_cast<unsigned char>(255* result + .5f);
        }
        else{
            float result = 1 - (2 * (1-img_1) * (1 - img));
            image_3->pixel_array[i] = static_cast<unsigned char>(255* result + .5f);
        }

    }
    return image_3;
}

void Image::scale_color(int i, int scale) {
    for (int j = i; j < 3 * header.width * header.height; j += 3) {
        float x = this->pixel_array[j];
        if (scale == 0) {
            this->pixel_array[j] = 0;
        } else if (x > 255 / scale) {
            this->pixel_array[j] = 255;
        } else {
            this->pixel_array[j] = this->pixel_array[j] * scale;
        }

    }

}
void Image::make_one_color(int j) {
    if (j == 0) {
        for (int i = 0; i < 3 * header.width * header.height; i++) {
            if (i % 3 == j + 1) {
                this->pixel_array[i] = this->pixel_array[i - 1];
            } else if (i % 3 == j + 2) {
                this->pixel_array[i] = this->pixel_array[i - 2];
            }
        }
    }
    else if (j == 1) {
        for (int i = 0; i < 3 * header.width * header.height; i++) {
            if (i % 3 == j + 1) {
                this->pixel_array[i] = this->pixel_array[i - 1];
            } else if (i % 3 == j - 1) {
                this->pixel_array[i] = this->pixel_array[i + 1];
            }
        }


    }
    else if (j == 2) {
        for (int i = 0; i < 3 * header.width * header.height; i++) {
            if (i % 3 == j - 2) {
                this->pixel_array[i] = this->pixel_array[i + 2];
            } else if (i % 3 == j - 1) {
                this->pixel_array[i] = this->pixel_array[i + 1];
            }
        }
    }
}

void Image::reverse(){
    int count = 0;
    int size = 3 * header.width * header.height;

    for(int i = size-1; i >= count; i-=3){
        for(int j = i-2; j <= i; j++) {
            unsigned char temp = this->pixel_array[j];
            this->pixel_array[j] = this->pixel_array[count];
            this->pixel_array[count] = temp;
            count++;
        }
    }

}

void Image::add_color(int j, int num_to_add){
    for(int i = j; i < header.height*header.width*3; i+=3){
        if(this->pixel_array[i] > (255-num_to_add)){
            this->pixel_array[i] = 255;
        }
        else if((this->pixel_array[i] + num_to_add) < 0){
            this->pixel_array[i] = 0;
        }
        else{
            this->pixel_array[i] += num_to_add;
        }

    }
}

