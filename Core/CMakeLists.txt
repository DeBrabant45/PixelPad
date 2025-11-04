# Core Layer

add_library(${PIXEL_PAD_CORE_TARGET_NAME}
    src/Graphics/Canvas.cpp
    include/Graphics/Canvas.hpp

    src/Graphics/CanvasSnapshot.cpp
    include/Graphics/CanvasSnapshot.hpp

    include/Tools/ITool.hpp

    src/Tools/PencilTool.cpp
    include/Tools/PencilTool.hpp

    src/Tools/LineTool.cpp
    include/Tools/LineTool.hpp

    src/Tools/EraserTool.cpp
    include/Tools/EraserTool.hpp

    src/Tools/FillTool.cpp
    include/Tools/FillTool.hpp

    src/Tools/RectangleTool.cpp
    include/Tools/RectangleTool.hpp

    src/Tools/EllipseTool.cpp
    include/Tools/EllipseTool.hpp

    include/Tools/DrawCommand.hpp

    include/Geometries/Transform.hpp

    include/Graphics/Color.hpp
)

target_include_directories(${PIXEL_PAD_CORE_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
