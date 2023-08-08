from PIL import Image
import os

def pixelate_smallar(input_file_path, output_file_path, pixel_size):
    original_image = Image.open(input_file_path)
    smaller_image = original_image.resize((pixel_size, pixel_size), Image.ANTIALIAS)
    smaller_image.save(output_file_path)


def process_directory_images(base_dir, pixel_size):
    for root, _, files in os.walk(base_dir):
        image_filename = None
        
        if "image.jpg" in files:
            image_filename = "image.jpg"
        elif "image.png" in files:
            image_filename = "image.png"
        
        if image_filename:
            image_path = os.path.join(root, image_filename)
            try:
                pixelate_smallar(image_path, image_path, pixel_size)
            except Exception as e:
                print(f"Error processing {image_path}: {e}")

process_directory_images(".", 300)

