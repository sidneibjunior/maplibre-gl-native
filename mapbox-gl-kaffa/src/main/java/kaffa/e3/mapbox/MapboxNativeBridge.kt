package kaffa.e3.mapbox

class MapboxNativeBridge {

    init {
        System.loadLibrary("mbgl-kaffa")
    }

    private var nativeMapPtr: Long = 0
    private var nativeHeadlessFrontendPtr: Long = 0
    private var imageBuffer = ByteArray(0);

    private external fun initializeN(width: Int, height: Int, lat: Double, lng: Double, zoom: Double, styleUrl: String, apyKey: String)

    private external fun setSizeN(width: Int, height: Int)

    private external fun jumpToN(lat: Double, lng: Double, zoom: Double)

    private external fun destroyN()

    fun initialize(width: Int, height: Int, lat: Double, lng: Double, zoom: Double, styleUrl: String, apyKey: String) {
        resizeBuffer(width, height)
        initializeN(width, height, lat, lng, zoom, styleUrl, apyKey)
    }

    fun destroy() {
        imageBuffer = ByteArray(0)
        destroyN()
    }

    fun jumpTo(lat: Double, lng: Double, zoom: Double) {
        jumpToN(lat, lng, zoom)
    }

    fun setSize(width: Int, height: Int) {
        resizeBuffer(width, height)
        setSizeN(width, height)
    }

    private fun resizeBuffer(width: Int, height: Int) {
        imageBuffer = ByteArray(width * height * 4)
    }
}

fun main() {
    val map = MapboxNativeBridge()
    println("**1")
    map.initialize(
        width = 300,
        height = 200,
        lat = -1.4014014,
        lng = -48.3721267,
        zoom = 12.78,
        styleUrl = "file:///home/sidnei-bernardo/git/kaffa/maplibre-gl-native/bin/mapbox-style.json",
        apyKey = ""
    );
    println("**2")
    map.jumpTo(-1.4014014, -48.3721267, 11.0)
    map.setSize(1200, 600)
    map.jumpTo(-1.4014014, -48.3721267, 13.0)

    println("**3")
    map.destroy()

//    MapboxNativeBridge().exportImage(
//        styleUrl = "/home/sidnei-bernardo/git/kaffa/espresso3/src/app-base/e3-app-base/src/main/resources/mapbox/mapbox-style.json",
//        outputFileName = "out.png"
//    )
}