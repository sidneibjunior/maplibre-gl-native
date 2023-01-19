package kaffa.e3.mapbox

class MapboxNativeBridge {

    init {
        System.loadLibrary("mbgl-render")
//        System.loadLibrary("mapbox-kaffa")
    }

    external fun exportImage(styleUrl: String, outputFileName: String);
}

fun main() {
    MapboxNativeBridge().exportImage(
        styleUrl = "/home/sidnei-bernardo/git/kaffa/espresso3/src/app-base/e3-app-base/src/main/resources/mapbox/mapbox-style.json",
        outputFileName = "out.png"
    )
}