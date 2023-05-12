package ar.edu.itba.cripto.bmpReader;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class BMPReader {

    public static void main(String[] args) throws IOException {
        BufferedImage image = null;
        try {
            File file = new File("src\\main\\java\\ar\\edu\\itba\\cripto\\bmpReader\\image.bmp");
            image = ImageIO.read(file);
        } catch (IOException e) {
            System.err.println("Error while opening image: " + e);
        }
        System.out.println("Image size: " + image.getWidth() + "x" + image.getHeight());
    }
}