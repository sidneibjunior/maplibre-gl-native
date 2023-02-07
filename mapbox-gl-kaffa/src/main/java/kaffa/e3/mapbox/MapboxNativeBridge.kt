package kaffa.e3.mapbox

import java.awt.image.BufferedImage
import java.io.File
import javax.imageio.ImageIO


class MapboxNativeBridge {

    init {
        System.loadLibrary("mbgl-kaffa")
    }

    private var width = 0
        get() = field

    private var height = 0
        get() = field

    private var nativeMapPtr: Long = 0
    private var nativeHeadlessFrontendPtr: Long = 0
    private var imageBuffer = ByteArray(0);

    private external fun initializeN(width: Int, height: Int, lat: Double, lng: Double, zoom: Double, styleUrl: String, apyKey: String)

    private external fun setSizeN(width: Int, height: Int)

    private external fun jumpToN(lat: Double, lng: Double, zoom: Double): ByteArray

    private external fun destroyN()

    fun initialize(width: Int, height: Int, lat: Double, lng: Double, zoom: Double, styleUrl: String) {
        resizeBuffer(width, height)
        initializeN(width, height, lat, lng, zoom, styleUrl, "")
    }

    fun destroy() {
        imageBuffer = ByteArray(0)
        destroyN()
    }

    fun jumpTo(lat: Double, lng: Double, zoom: Double): ByteArray {
        return jumpToN(lat, lng, zoom)
    }

    fun setSize(width: Int, height: Int) {
        resizeBuffer(width, height)
        setSizeN(width, height)
    }

    private fun resizeBuffer(width: Int, height: Int) {
        this.width = width
        this.height = height
        imageBuffer = ByteArray(width * height * 4)
    }
}

fun main() {
    val map = MapboxNativeBridge()
    map.initialize(
        width = 300,
        height = 200,
        lat = -1.4014014,
        lng = -48.3721267,
        zoom = 12.78,
        styleUrl = "file:///home/sidnei-bernardo/git/kaffa/maplibre-gl-native/bin/mapbox-style.json"
    );
    val ret = map.jumpTo(-1.4514014, -48.3721267, 13.0)
    val retInt = IntArray(ret.size)
    ret.forEachIndexed { index, byte ->
        retInt[index] = byte.int()
    }

    val img = BufferedImage(300, 200, BufferedImage.TYPE_INT_ARGB)
    img.raster.setPixels(0, 0, 300, 200, retInt)

    val outputfile = File("out2.png")
    ImageIO.write(img, "png", outputfile)

    map.destroy()
}

fun Byte.int(): Int = toInt() and 0xff