package kaffa.e3.mapbox

class MapboxNativeBridge {

    init {
        System.loadLibrary("mbgl-kaffa")
    }

    private var mapPtr: Long = 0

    external fun initialize(width: Int, height: Int, lat: Double, lng: Double, zoom: Double, styleUrl: String)

    external fun destroy()

    external fun jumpTo(lat: Double, lng: Double, zoom: Double)

    external fun setSize(width: Int, height: Int)
}

fun main() {
    val map = MapboxNativeBridge()
    map.initialize(2, 3, 2.2, 3.3, 3.0, "");
    map.jumpTo(2.2, 3.3, 1.0)
    map.destroy()

//    MapboxNativeBridge().exportImage(
//        styleUrl = "/home/sidnei-bernardo/git/kaffa/espresso3/src/app-base/e3-app-base/src/main/resources/mapbox/mapbox-style.json",
//        outputFileName = "out.png"
//    )
}