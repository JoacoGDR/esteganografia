package ar.edu.itba.cripto.bmpReader;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.io.ByteArrayInputStream;
import java.io.InputStream;

public class BMPReader {
    
    final static String PATH = "src\\main\\java\\ar\\edu\\itba\\cripto\\bmpReader";

    //source: https://github.com/FabianNorbertoEscobar
    public static byte[] imageToByteArray(BufferedImage image) throws IOException {
		ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
		ImageIO.write(image, "bmp", byteArrayOutputStream);
		byteArrayOutputStream.flush();
		byte[] imageByteArray = byteArrayOutputStream.toByteArray();
		byteArrayOutputStream.close();
		return imageByteArray;
	}

    //source: https://github.com/FabianNorbertoEscobar
    public static BufferedImage byteArrayToImage(byte[] imageByteArray) throws IOException {
		InputStream inputStream = new ByteArrayInputStream(imageByteArray);
		BufferedImage bufferedImage = ImageIO.read(inputStream);
		inputStream.close();
		return bufferedImage;
	}

    public static BufferedImage bmpReader(String pathname) {
        BufferedImage image = null;
        try {
            File file = new File(pathname);
            image = ImageIO.read(file);
        } catch (IOException e) {
            System.err.println("Error while opening image: " + e);
        }
        return image;
    }

    public static void bmpWriter(BufferedImage image, String pathname) {
        try {
            File outputfile = new File(pathname);
            ImageIO.write(image, "bmp", outputfile);
        } catch (IOException e) {
            System.err.println("Error while saving image: " + e);
        }
        System.out.println("Image saved");
    }

    public static void main(String[] args) throws IOException {
        BufferedImage image = bmpReader(PATH + "\\image.bmp");
        byte[] imageByteArray = imageToByteArray(image);
        System.out.println("Image size: " + image.getWidth() + "x" + image.getHeight());
        //cambio el bytearray
        for (int i = 200; i < imageByteArray.length; i++) {
            imageByteArray[i] = 55;
        }
        image = byteArrayToImage(imageByteArray);
        bmpWriter(image, PATH + "\\image2.bmp");
    }
}