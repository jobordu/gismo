
#include <gsCore/gsTemplateTools.h>

#include <gsCore/gsGeometry.h>
#include <gsCore/gsBasis.h>
#include <gsCore/gsGeometryEvaluator.h>
#include <gsCore/gsGeometryEvaluator.hpp>


namespace gismo
{
    CLASS_TEMPLATE_INST gsGenericGeometryEvaluator<real_t,4, 0>;
    CLASS_TEMPLATE_INST gsGenericGeometryEvaluator<real_t,4, 1>;
    CLASS_TEMPLATE_INST gsGenericGeometryEvaluator<real_t,4,-3>;
}
