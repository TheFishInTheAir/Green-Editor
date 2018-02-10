function (green_engine_libs includes libs)
###
### Libraries
###

set(SUPPORTS_VULKAN FALSE) # Check if os Supports Vulkan

if(WIN32)# Check if OS is Windows (Supports Vulkan)
    set(SUPPORTS_VULKAN TRUE)
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux") # Check if OS is Linux (Supports Vulkan)
    set(SUPPORTS_VULKAN TRUE) # Check if os Supports Vulkan
endif()



list(APPEND Green_Engine_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/libs/headers) #Define the Green Engine include directories



find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message("${OPENGL_INCLUDE_DIRS} and ${OPENGL_LIBRARIES}\n")
    list(APPEND Green_Engine_INCLUDES ${OPENGL_INCLUDE_DIRS})
    list(APPEND Green_Engine_LIBS ${OPENGL_LIBRARIES})
endif ()


find_package(GLEWosd REQUIRED)

if (GLEW_FOUND)
    message("${GLEW_INCLUDE_DIR} and ${GLEW_LIBRARY}\n")
    list(APPEND Green_Engine_INCLUDES ${GLEW_INCLUDE_DIR})
    list(APPEND Green_Engine_LIBS ${GLEW_LIBRARY})

endif()

find_package(GLFWosd REQUIRED)

if (GLFW_FOUND)
    message("${GLFW_INCLUDE_DIR} and ${GLFW_LIBRARY}\n")
    list(APPEND Green_Engine_INCLUDES ${GLFW_INCLUDE_DIR})
    list(APPEND Green_Engine_LIBS ${GLFW_LIBRARY})

endif()



if (SUPPORTS_VULKAN)

    message("Should support Vulkan")
    find_package(Vulkan)

    if(Vulkan_FOUND)

        list(APPEND Green_Engine_INCLUDES ${Vulkan_INCLUDE_DIRS})
        list(APPEND Green_Engine_LIBS ${Vulkan_LIBRARIES})

    else()
		
		if(IS_DIRECTORY $ENV{VULKAN_SDK})

			list(APPEND Green_Engine_INCLUDES	$ENV{VULKAN_SDK}/Include)
			list(APPEND Green_Engine_LIBS		$ENV{VULKAN_SDK}/Lib/vulkan-1.lib)

		endif()
		
        message( ERROR ": Could not Find Vulkan, Vulkan is a good for Windows and Linux")

    endif()

elseif(APPLE)
    #TODO: try catch
    message("Should support Metal")
    find_library(Cocoa_LIBRARY Cocoa)
    find_library(Core_LIBRARY CoreFoundation)
    find_library(Metal_LIBRARY Metal)
    find_library(MetalKit_LIBRARY MetalKit)
    message("Cocoa: ${Cocoa_LIBRARY}")
    message("CoreFoundation: ${Core_LIBRARY}")
    message("Metal: ${Metal_LIBRARY}")
    message("MetalKit: ${MetalKit_LIBRARY}")
    #list(APPEND Green_Engine_INCLUDES ${Vulkan_INCLUDE_DIRS}/Headers)

    list(APPEND Green_Engine_LIBS ${Cocoa_LIBRARY})
    list(APPEND Green_Engine_LIBS ${Core_LIBRARY})
    list(APPEND Green_Engine_LIBS ${Metal_LIBRARY})
    list(APPEND Green_Engine_LIBS ${MetalKit_LIBRARY})
    list(APPEND Green_Engine_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs/compiled/mtlpp.o ${CMAKE_CURRENT_SOURCE_DIR}/libs/compiled/window.o )
endif()


    ###
    ### pre-built libs TODO: make build system for them. Also make cross platform
    ###

    #list(APPEND Green_Engine_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs/compiled/libz.a )
    
	if(WIN32)
		set(ASSIMP_ROOT_DIR CACHE PATH "ASSIMP root directory")

		set(ASSIMP_ROOT_DIR "C:\\Program Files\\Assimp")

	else()

	endif()

	find_package(assimp REQUIRED)

	if(ASSIMP_LIBRARY_DIR)
		message("assimp: ${ASSIMP_INCLUDE_DIR}")
        list(APPEND Green_Engine_INCLUDES ${ASSIMP_INCLUDE_DIR})
        list(APPEND Green_Engine_LIBS ${ASSIMP_LIBRARY_RELEASE})

		#ZLIB

		list(APPEND Green_Engine_LIBS ${ASSIMP_LIBRARY_DIR}/zlibstatic.lib)

	endif()

    if(assimp_INCLUDE_DIRS)

        message("assimp: ${ASSIMP_INCLUDE_DIR}")
        list(APPEND Green_Engine_INCLUDES ${assimp_INCLUDE_DIRs})
        list(APPEND Green_Engine_LIBS ${assimp_LIBRARIES})

        #ZLIB
        if(WIN32)
            list(APPEND Green_Engine_LIBS ${assimp_LIBRARY_DIRS}/zlibstatic.lib)
        else()
            find_library(Z_LIB z)
            message("ZLIB: ${Z_LIB}")
            list(APPEND Green_Engine_LIBS ${Z_LIB})
        endif()



    endif()

    set(${includes} ${Green_Engine_INCLUDES} PARENT_SCOPE)
    set(${libs}     ${Green_Engine_LIBS}     PARENT_SCOPE)
    message("libs: ${Green_Engine_INCLUDES}")
    message("includes: ${Green_Engine_LIBS}")
endfunction()