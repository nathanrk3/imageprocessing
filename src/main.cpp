#include <iostream>
#include <cstring>
#include "image.h"


bool check_valid_file(const std::string& fileName){
    if(fileName.length() < 4 || fileName.substr(fileName.length()-4) != ".tga"){
        std::cout << "Invalid file name.x" <<std::endl;
        return false;
    }
    else{
        std::ifstream check_if_open(fileName);
        if(!check_if_open.is_open()){
            std::cout << "File does not exist." <<std::endl;
            return false;
        }
    }
    return true;
}


int main(int argc, const char** argv) {


    if(argc < 2 || !std::strcmp(argv[1], "--help")){
        std::cout << "HELP HELP" << std::endl;
    }
    else{


        int count = argc;
        std::string output_file = argv[1];
        if(output_file.length() >= 4){
            std::string file_type = output_file.substr(output_file.length() - 4);
            if(file_type != ".tga"){
                std::cout << "Invalid file name." << std::endl;
            }
            else{
                if(argc < 3 || std::string(argv[2]).substr(std::string(argv[2]).length()-4)!= ".tga"){
                    std::cout << "Invalid file name." <<std::endl;
                }
                else{
                    std::string tracking_file_name = argv[2];
                    std::ifstream check_if_open(tracking_file_name);
                    if(!check_if_open.is_open()){
                        std::cout << "File does not exist." <<std::endl;
                    }
                    else{
                        int checker = 1;
                        Image* output_image = new Image(tracking_file_name);
                        Image* temp = nullptr;

                        for(int i = 3; i < count; i++){
                            if(!std::strcmp(argv[i], "multiply")){
                                if(i == count-1){
                                    std::cout << "Missing argument.";
                                    checker = 0;
                                    break;
                                }
                                else{
                                    if(check_valid_file(std::string(argv[i+1]))){
                                        std::string name = std::string(argv[i+1]);
                                        Image next(name);
                                        temp = output_image->multiply(*output_image, next);
                                        delete output_image;
                                        output_image = temp;
                                        i++;


                                    }
                                    else{
                                        std::cout << "Invalid file name." << std::endl;
                                        checker = 0;
                                        break;
                                    }

                                }

                            }

                            else if(!std::strcmp(argv[i], "subtract")){
                                if(i == count-1){
                                    std::cout << "Missing argument.";
                                    checker = 0;
                                    break;
                                }
                                else{
                                    if(check_valid_file(std::string(argv[i+1]))){
                                        std::string name = std::string(argv[i+1]);
                                        Image next(name);
                                        temp = output_image->subtract(next);
                                        delete output_image;
                                        output_image = temp;
                                        i++;
                                    }
                                    else{
                                        checker = 0;
                                        break;
                                    }
                                }
                            }

                            else if(!std::strcmp(argv[i], "overlay")){
                                if(i == count-1){
                                    std::cout << "Missing argument.";
                                    checker = 0;
                                    break;
                                }
                                else{
                                    if(check_valid_file(std::string(argv[i+1]))){
                                        std::string name = std::string(argv[i+1]);
                                        Image next(name);
                                        temp = output_image->overlay(next);
                                        delete output_image;
                                        output_image = temp;
                                        i++;
                                    }
                                    else{
                                        checker = 0;
                                        break;
                                    }
                                }
                            }

                            else if(!std::strcmp(argv[i], "screen")){

                                if(i == count-1){
                                    std::cout << "Missing argument.";
                                    checker = 0;
                                    break;
                                }
                                else{
                                    if(check_valid_file(std::string(argv[i+1]))){
                                        std::string name = std::string(argv[i+1]);
                                        Image next(name);
                                        temp = output_image->screen(next);
                                        delete output_image;
                                        output_image = temp;
                                        i++;
                                    }
                                    else{
                                        checker = 0;
                                        break;
                                    }
                                }
                            }

                            else if(!std::strcmp(argv[i], "flip")){
                                output_image->reverse();
                            }

                            else if(!std::strcmp(argv[i], "addblue")){
                                if(i == count-1){
                                    std::cout << "Missing argument.";
                                    checker = 0;
                                    break;
                                }
                                else{
                                    try{
                                    std::string howmuch = argv[i+1];
                                    output_image->add_color(0, std::stoi(howmuch));
                                    i++;
                                    }
                                    catch(const std::invalid_argument& error){
                                        std::cout << "Invalid argument, expected number." <<std::endl;
                                        checker=0;
                                        break;


                                    }

                                }
                            }
                            else if(!std::strcmp(argv[i], "addgreen")){
                                if(i == count-1){
                                    std::cout << "Missing argument.";
                                    checker = 0;
                                    break;
                                }
                                else{
                                    try{
                                        std::string howmuch = argv[i+1];
                                        output_image->add_color(1, std::stoi(howmuch));
                                        i++;
                                    }
                                    catch(const std::invalid_argument& error){
                                        std::cout << "Invalid argument, expected number." <<std::endl;
                                        checker=0;
                                        break;


                                    }

                                }
                            }

                            else if(!std::strcmp(argv[i], "addred")){
                                if(i == count-1){
                                    std::cout << "Missing argument.";
                                    checker = 0;
                                    break;
                                }
                                else{
                                    try{
                                        std::string howmuch = argv[i+1];
                                        output_image->add_color(2, std::stoi(howmuch));
                                        i++;
                                    }
                                    catch(const std::invalid_argument& error){
                                        std::cout << "Invalid argument, expected number." <<std::endl;
                                        checker=0;
                                        break;


                                    }

                                }
                            }
                            else if(!std::strcmp(argv[i], "scalegreen")){
                                if(i == count-1){
                                    std::cout << "Missing argument.";
                                    checker = 0;
                                    break;
                                }

                                else{
                                    try{
                                        std::string howmuch = argv[i+1];
                                        output_image->scale_color(1, std::stoi(howmuch));
                                        i++;
                                    }
                                    catch(const std::invalid_argument& error){
                                        std::cout << "Invalid argument, expected number." <<std::endl;
                                        checker=0;
                                        break;


                                    }}


                                }

                                else if(!std::strcmp(argv[i], "scaleblue")){
                                    if(i == count-1){
                                        std::cout << "Missing argument.";
                                        checker = 0;
                                        break;
                                    }

                                    else{
                                        try{
                                            std::string howmuch = argv[i+1];
                                            output_image->scale_color(0, std::stoi(howmuch));
                                            i++;
                                        }
                                        catch(const std::invalid_argument& error){
                                            std::cout << "Invalid argument, expected number." <<std::endl;
                                            checker=0;
                                            break;


                                        }
                                    }

                                }

                                else if(!std::strcmp(argv[i], "scalered")){
                                    if(i == count-1){
                                        std::cout << "Missing argument.";
                                        checker = 0;
                                        break;
                                    }

                                    else{
                                        try{
                                            std::string howmuch = argv[i+1];
                                            output_image->scale_color(2, std::stoi(howmuch));
                                            i++;
                                        }
                                        catch(const std::invalid_argument& error){
                                            std::cout << "Invalid argument, expected number." <<std::endl;
                                            checker=0;
                                            break;


                                        }
                                    }


                                }

                                else if(!std::strcmp(argv[i], "onlyblue")){
                                    output_image->make_one_color(0);
                                }

                                else if(!std::strcmp(argv[i], "onlygreen")){
                                    output_image->make_one_color(1);
                                }

                                else if(!std::strcmp(argv[i], "onlygreen")){
                                    output_image->make_one_color(2);
                                }

                                else if(!std::strcmp(argv[i], "combine")){
                                    if(argc < i +2){
                                        std::cout << "Missing argument." << std::endl;
                                        checker = 0;
                                        return 0;
                                    }
                                    else{

                                        if(check_valid_file(argv[i+1]) && check_valid_file(argv[i+2])){
                                            Image img_blue(argv[i+2]);
                                            Image img_green(argv[i+1]);

                                            for(int j = 0; j < output_image->header.width * output_image->header.height * 3; j +=3){

                                                output_image->pixel_array[j] = img_blue.pixel_array[j];
                                                output_image->pixel_array[j+1] = img_green.pixel_array[j+1];
                                        }
                                    }
                                        else{
                                            std::cout << "Invalid argument, file does not exist.";
                                            checker = 0;
                                            return 0;

                                        }
                                    }

                                }








                        }
                        if(checker){
                            output_image->write_to(output_file);
                        }
                        delete output_image;

                    }



                }


            }
        }
        else{
            std::cout << "Invalid file name." << std::endl;
        }
    }





    return 0;

}

