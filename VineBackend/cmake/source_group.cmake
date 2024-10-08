file(GLOB VINE_CORE
    "${VINE_BACKEND_INC_PATH}/vine/core/*.h"
    "${VINE_BACKEND_SRC_PATH}/core/*.cpp"
)

file(GLOB VINE_CORE_CODES
    "${VINE_BACKEND_INC_PATH}/vine/core/codes/*.h"
    "${VINE_BACKEND_SRC_PATH}/core/codes/*.cpp"
)

file(GLOB VINE_EVENTS
    "${VINE_BACKEND_INC_PATH}/vine/events/*.h"
    "${VINE_BACKEND_SRC_PATH}/events/*.cpp"
)

file(GLOB VINE_RENDERER
    "${VINE_BACKEND_INC_PATH}/vine/renderer/*.h"
    "${VINE_BACKEND_SRC_PATH}/renderer/*.cpp"
)

file(GLOB VINE_RENDERER_BACKEND
    "${VINE_BACKEND_INC_PATH}/vine/renderer/backend/*.h"
    "${VINE_BACKEND_SRC_PATH}/renderer/backend/*.cpp"
)

file(GLOB VINE_RENDERER_RENDERABLE
    "${VINE_BACKEND_INC_PATH}/vine/renderer/renderable/*.h"
    "${VINE_BACKEND_SRC_PATH}/renderer/renderable/*.cpp"
)

file(GLOB VINE_UTIL
    "${VINE_BACKEND_INC_PATH}/vine/util/*.h"
    "${VINE_BACKEND_SRC_PATH}/util/*.cpp"
)

file(GLOB VINE_WINDOW
    "${VINE_BACKEND_INC_PATH}/vine/window/*.h"
    "${VINE_BACKEND_SRC_PATH}/window/*.cpp"
)

file(GLOB VINE_RESOURCE
    "${VINE_BACKEND_INC_PATH}/vine/resource/*.h"
    "${VINE_BACKEND_SRC_PATH}/resource/*.cpp"
)

file(GLOB VINE_SCRIPT
    "${VINE_BACKEND_INC_PATH}/vine/script/*.h"
    "${VINE_BACKEND_SRC_PATH}/script/*.cpp"
)

source_group("core" FILES ${VINE_CORE})
source_group("core\\codes" FILES ${VINE_CORE_CODES})
source_group("events" FILES ${VINE_EVENTS})
source_group("renderer" FILES ${VINE_RENDERER})
source_group("renderer\\backend" FILES ${VINE_RENDERER_BACKEND})
source_group("renderer\\renderable" FILES ${VINE_RENDERER_RENDERABLE})
source_group("util" FILES ${VINE_UTIL})
source_group("window" FILES ${VINE_WINDOW})
source_group("resource" FILES ${VINE_RESOURCE})
source_group("script" FILES ${VINE_SCRIPT})