#include <stdio.h>
#include "MapboxNativeBridge.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <mbgl/map/map.hpp>
#include <mbgl/map/map_options.hpp>
#include <mbgl/util/image.hpp>
#include <mbgl/util/run_loop.hpp>

#include <args.hxx>

#include <mbgl/gfx/backend.hpp>
#include <mbgl/gfx/headless_frontend.hpp>
#include <mbgl/style/style.hpp>

#include "jni_utils.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace mbgl;

jfieldID getMapPtrField(JNIEnv * env, jobject obj) {
    static jfieldID mapFieldId = 0;
    if (!mapFieldId) {
        jclass c = env->GetObjectClass(obj);
        mapFieldId = env->GetFieldID(c, "nativeMapPtr", "J");
        env->DeleteLocalRef(c);
    }
    return mapFieldId;
}

jfieldID getFrontendPtrField(JNIEnv * env, jobject obj) {
    static jfieldID feFieldId = 0;
    if (!feFieldId) {
        jclass c = env->GetObjectClass(obj);
        feFieldId = env->GetFieldID(c, "nativeHeadlessFrontendPtr", "J");
        env->DeleteLocalRef(c);
    }
    return feFieldId;
}

void setMapPtr(JNIEnv *env, jobject obj, Map *mapObj) {
    env->SetLongField(obj, getMapPtrField(env, obj), (jlong) mapObj);
}

void setFrontendPtr(JNIEnv *env, jobject obj, HeadlessFrontend *feObj) {
    env->SetLongField(obj, getFrontendPtrField(env, obj), (jlong) feObj);
}

Map* getMapObj(JNIEnv *env, jobject obj) {
    return (Map*) env->GetLongField(obj, getMapPtrField(env, obj));
}

HeadlessFrontend* getFrontendObj(JNIEnv *env, jobject obj) {
    return (HeadlessFrontend*) env->GetLongField(obj, getFrontendPtrField(env, obj));
}

util::RunLoop loop;

JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_initializeN(JNIEnv *env, jobject obj, jint width, jint height, jdouble lat, jdouble lng, jdouble zoom, jstring styleUrl, jstring apiKey) {
    using namespace mbgl;

    auto mapTilerConfiguration = TileServerOptions::MapTilerConfiguration();
    std::string styleStr = Utils::jstring2str(styleUrl, env);
    std::string apiKeyStr = Utils::jstring2str(apiKey, env);

    HeadlessFrontend *frontend = new HeadlessFrontend({(uint32_t)width, (uint32_t)height}, 1);
    setFrontendPtr(env, obj, frontend);

    Map *map = new Map(*frontend, MapObserver::nullObserver(),
            MapOptions().withMapMode(MapMode::Static).withSize(frontend->getSize()).withPixelRatio(1),
            ResourceOptions().withCachePath("cache.sqlite").withAssetPath(".").withApiKey(apiKeyStr).withTileServerOptions(mapTilerConfiguration));
    map->getStyle().loadURL(styleStr);
    setMapPtr(env, obj, map);

    return;
}

JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_destroyN(JNIEnv *env, jobject obj) {
    Map* map = getMapObj(env, obj);
    HeadlessFrontend* frontend = getFrontendObj(env, obj);
    delete map;
    delete frontend;
    return;
}

JNIEXPORT jbyteArray JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_jumpToN(JNIEnv *env, jobject obj, jdouble lat, jdouble lng, jdouble zoom) {
    Map* map = getMapObj(env, obj);
    HeadlessFrontend* frontend = getFrontendObj(env, obj);
    
    map->jumpTo(CameraOptions()
                   .withCenter(LatLng { lat, lng })
                   .withZoom(zoom));

    PremultipliedImage image = frontend->render(*map).image;

    int size = image.bytes();
    jbyteArray ret = Utils::toJavaByteArray(env, image.data.get(), size);
     try {
         std::ofstream out("out.png", std::ios::binary);
         out << encodePNG(frontend->render(*map).image);
         out.close();
     } catch(std::exception& e) {
         std::cout << "Error: " << e.what() << std::endl;
         exit(1);
     }
    return ret;


    // return;
}

JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_setSizeN(JNIEnv *env, jobject obj, jint width, jint height) {
    HeadlessFrontend* frontend = getFrontendObj(env, obj);
    Map* map = getMapObj(env, obj);
    
    frontend->setSize({(uint32_t)width, (uint32_t)height});
    map->setSize({(uint32_t)width, (uint32_t)height});
    
    return;
}
