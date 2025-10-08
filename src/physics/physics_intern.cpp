// Copyright (c) Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#include "joltc.h"

#ifdef _MSC_VER
__pragma(warning(push, 0))
#endif

#include "Jolt/Jolt.h"
#include "Jolt/RegisterTypes.h"
#include "Jolt/Core/Factory.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Physics/PhysicsSettings.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/Physics/Collision/CollideShape.h"
#include "Jolt/Physics/Collision/Shape/BoxShape.h"
#include "Jolt/Physics/Collision/Shape/SphereShape.h"
#include "Jolt/Physics/Collision/Shape/TriangleShape.h"
#include "Jolt/Physics/Collision/Shape/CapsuleShape.h"
#include "Jolt/Physics/Collision/Shape/TaperedCapsuleShape.h"
#include "Jolt/Physics/Collision/Shape/CylinderShape.h"
#include "Jolt/Physics/Collision/Shape/ConvexHullShape.h"
#include "Jolt/Physics/Collision/CastResult.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Body/BodyActivationListener.h"
#include "Jolt/Physics/Body/AllowedDOFs.h"
#include "Jolt/Physics/Constraints/SixDOFConstraint.h"
#include "Jolt/Physics/Character/CharacterBase.h"
#include "Jolt/Physics/Character/CharacterID.h"
#include "Jolt/Physics/Collision/Shape/MeshShape.h"
#include "Jolt/Physics/Vehicle/VehicleTransmission.h"

#ifdef DEBUG_RENDERER
#include <Jolt/Renderer/DebugRendererSimple.h>
#endif // DEBUG_RENDERER

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

#define ENSURE_SIZE_ALIGN(type0, type1) \
    static_assert(sizeof(type0) == sizeof(type1)); \
    static_assert(alignof(type0) == alignof(type1))

// Ensure that we use 32-bit object layers
static_assert(sizeof(ObjectLayer) == 4);

static_assert(sizeof(ObjectLayer) == sizeof(ObjectLayer));
static_assert(sizeof(BroadPhaseLayer) == sizeof(BroadPhaseLayer));
static_assert(sizeof(BodyID) == sizeof(BodyID));
static_assert(sizeof(SubShapeID) == sizeof(SubShapeID));
static_assert(sizeof(CharacterID) == sizeof(CharacterID));
static_assert(sizeof(CollisionGroup::GroupID) == sizeof(CollisionGroupID));
static_assert(sizeof(CollisionGroup::SubGroupID) == sizeof(CollisionSubGroupID));

static_assert(INVALID_COLLISION_GROUP_ID == (int)CollisionGroup::cInvalidGroup);
static_assert(INVALID_COLLISION_SUBGROUP_ID == (int)CollisionGroup::cInvalidSubGroup);


// EPhysicsUpdateError
static_assert(sizeof(PhysicsUpdateError) == sizeof(EPhysicsUpdateError));
static_assert(PhysicsUpdateError_None == (int)EPhysicsUpdateError::None);
static_assert(PhysicsUpdateError_ManifoldCacheFull == (int)EPhysicsUpdateError::ManifoldCacheFull);
static_assert(PhysicsUpdateError_BodyPairCacheFull == (int)EPhysicsUpdateError::BodyPairCacheFull);
static_assert(PhysicsUpdateError_ContactConstraintsFull == (int)EPhysicsUpdateError::ContactConstraintsFull);

// EBodyType
static_assert(BodyType_Rigid == (int)EBodyType::RigidBody);
static_assert(BodyType_Soft == (int)EBodyType::SoftBody);

// EMotionType
static_assert(MotionType_Static == (int)EMotionType::Static);
static_assert(MotionType_Kinematic == (int)EMotionType::Kinematic);
static_assert(MotionType_Dynamic == (int)EMotionType::Dynamic);

// EActivation
static_assert(sizeof(EActivation) == sizeof(Activation));
static_assert(Activation_Activate == (int)EActivation::Activate);
static_assert(Activation_DontActivate == (int)EActivation::DontActivate);

// EActivation
static_assert(sizeof(ValidateResult) == sizeof(ValidateResult));
static_assert(ValidateResult_AcceptAllContactsForThisBodyPair == (int)ValidateResult::AcceptAllContactsForThisBodyPair);
static_assert(ValidateResult_AcceptContact == (int)ValidateResult::AcceptContact);
static_assert(ValidateResult_RejectContact == (int)ValidateResult::RejectContact);
static_assert(ValidateResult_RejectAllContactsForThisBodyPair == (int)ValidateResult::RejectAllContactsForThisBodyPair);

// EShapeType
static_assert(ShapeType_Convex == (int)EShapeType::Convex);
static_assert(ShapeType_Compound == (int)EShapeType::Compound);
static_assert(ShapeType_Decorated == (int)EShapeType::Decorated);
static_assert(ShapeType_Mesh == (int)EShapeType::Mesh);
static_assert(ShapeType_HeightField == (int)EShapeType::HeightField);
static_assert(ShapeType_SoftBody == (int)EShapeType::SoftBody);
static_assert(ShapeType_User1 == (int)EShapeType::User1);
static_assert(ShapeType_User2 == (int)EShapeType::User2);
static_assert(ShapeType_User3 == (int)EShapeType::User3);
static_assert(ShapeType_User4 == (int)EShapeType::User4);

// EShapeSubType
static_assert(ShapeSubType_Sphere == (int)EShapeSubType::Sphere);
static_assert(ShapeSubType_Box == (int)EShapeSubType::Box);
static_assert(ShapeSubType_Triangle == (int)EShapeSubType::Triangle);
static_assert(ShapeSubType_Capsule == (int)EShapeSubType::Capsule);
static_assert(ShapeSubType_TaperedCapsule == (int)EShapeSubType::TaperedCapsule);
static_assert(ShapeSubType_Cylinder == (int)EShapeSubType::Cylinder);
static_assert(ShapeSubType_ConvexHull == (int)EShapeSubType::ConvexHull);
static_assert(ShapeSubType_StaticCompound == (int)EShapeSubType::StaticCompound);
static_assert(ShapeSubType_MutableCompound == (int)EShapeSubType::MutableCompound);
static_assert(ShapeSubType_RotatedTranslated == (int)EShapeSubType::RotatedTranslated);
static_assert(ShapeSubType_Scaled == (int)EShapeSubType::Scaled);
static_assert(ShapeSubType_OffsetCenterOfMass == (int)EShapeSubType::OffsetCenterOfMass);
static_assert(ShapeSubType_Mesh == (int)EShapeSubType::Mesh);
static_assert(ShapeSubType_HeightField == (int)EShapeSubType::HeightField);
static_assert(ShapeSubType_SoftBody == (int)EShapeSubType::SoftBody);

// EConstraintType
static_assert(ConstraintType_Constraint == (int)EConstraintType::Constraint);
static_assert(ConstraintType_TwoBodyConstraint == (int)EConstraintType::TwoBodyConstraint);

// EConstraintSubType
static_assert(ConstraintSubType_Fixed == (int)EConstraintSubType::Fixed);
static_assert(ConstraintSubType_Point == (int)EConstraintSubType::Point);
static_assert(ConstraintSubType_Hinge == (int)EConstraintSubType::Hinge);
static_assert(ConstraintSubType_Slider == (int)EConstraintSubType::Slider);
static_assert(ConstraintSubType_Distance == (int)EConstraintSubType::Distance);
static_assert(ConstraintSubType_Cone == (int)EConstraintSubType::Cone);
static_assert(ConstraintSubType_SwingTwist == (int)EConstraintSubType::SwingTwist);
static_assert(ConstraintSubType_SixDOF == (int)EConstraintSubType::SixDOF);
static_assert(ConstraintSubType_Path  == (int)EConstraintSubType::Path);
static_assert(ConstraintSubType_Vehicle == (int)EConstraintSubType::Vehicle);
static_assert(ConstraintSubType_RackAndPinion == (int)EConstraintSubType::RackAndPinion);
static_assert(ConstraintSubType_Gear == (int)EConstraintSubType::Gear);
static_assert(ConstraintSubType_Pulley == (int)EConstraintSubType::Pulley);

static_assert(ConstraintSubType_User1 == (int)EConstraintSubType::User1);
static_assert(ConstraintSubType_User2 == (int)EConstraintSubType::User2);
static_assert(ConstraintSubType_User3 == (int)EConstraintSubType::User3);
static_assert(ConstraintSubType_User4 == (int)EConstraintSubType::User4);

// EActivation
static_assert(sizeof(EConstraintSpace) == sizeof(ConstraintSpace));
static_assert(ConstraintSpace_LocalToBodyCOM == (int)EConstraintSpace::LocalToBodyCOM);
static_assert(ConstraintSpace_WorldSpace == (int)EConstraintSpace::WorldSpace);

// EMotionQuality
static_assert(MotionQuality_Discrete == (int)EMotionQuality::Discrete);
static_assert(MotionQuality_LinearCast == (int)EMotionQuality::LinearCast);

// EOverrideMassProperties
static_assert(sizeof(OverrideMassProperties) == sizeof(uint32_t));
static_assert(sizeof(EOverrideMassProperties) == sizeof(uint8_t));
static_assert(OverrideMassProperties_CalculateMassAndInertia == (int)EOverrideMassProperties::CalculateMassAndInertia);
static_assert(OverrideMassProperties_CalculateInertia == (int)EOverrideMassProperties::CalculateInertia);
static_assert(OverrideMassProperties_MassAndInertiaProvided == (int)EOverrideMassProperties::MassAndInertiaProvided);

// EAllowedDOFs
static_assert(sizeof(AllowedDOFs) == sizeof(uint32_t));
static_assert(AllowedDOFs_All == (int)EAllowedDOFs::All);
static_assert(AllowedDOFs_TranslationX == (int)EAllowedDOFs::TranslationX);
static_assert(AllowedDOFs_TranslationY == (int)EAllowedDOFs::TranslationY);
static_assert(AllowedDOFs_TranslationZ == (int)EAllowedDOFs::TranslationZ);
static_assert(AllowedDOFs_RotationX == (int)EAllowedDOFs::RotationX);
static_assert(AllowedDOFs_RotationY == (int)EAllowedDOFs::RotationY);
static_assert(AllowedDOFs_RotationZ == (int)EAllowedDOFs::RotationZ);
static_assert(AllowedDOFs_Plane2D == (int)EAllowedDOFs::Plane2D);

// MotorState
static_assert(sizeof(MotorState) == sizeof(uint32_t));
static_assert(MotorState_Off == (int)EMotorState::Off);
static_assert(MotorState_Velocity == (int)EMotorState::Velocity);
static_assert(MotorState_Position == (int)EMotorState::Position);

// SwingType
static_assert(sizeof(SwingType) == sizeof(uint32_t));
static_assert(SwingType_Cone == (int)ESwingType::Cone);
static_assert(SwingType_Pyramid == (int)ESwingType::Pyramid);

// SixDOFConstraintAxis
static_assert(sizeof(SixDOFConstraintAxis) == sizeof(uint32_t));
static_assert(SixDOFConstraintAxis_TranslationX == (int)SixDOFConstraintSettings::EAxis::TranslationX);
static_assert(SixDOFConstraintAxis_TranslationY == (int)SixDOFConstraintSettings::EAxis::TranslationY);
static_assert(SixDOFConstraintAxis_TranslationZ == (int)SixDOFConstraintSettings::EAxis::TranslationZ);
static_assert(SixDOFConstraintAxis_RotationX == (int)SixDOFConstraintSettings::EAxis::RotationX);
static_assert(SixDOFConstraintAxis_RotationY == (int)SixDOFConstraintSettings::EAxis::RotationY);
static_assert(SixDOFConstraintAxis_RotationZ == (int)SixDOFConstraintSettings::EAxis::RotationZ);

// SpringMode
static_assert(sizeof(SpringMode) == sizeof(uint32_t));
static_assert(SpringMode_FrequencyAndDamping == (int)ESpringMode::FrequencyAndDamping);
static_assert(SpringMode_StiffnessAndDamping == (int)ESpringMode::StiffnessAndDamping);

// EGroundState
static_assert(sizeof(CharacterBase::EGroundState) == sizeof(GroundState));
static_assert(GroundState_OnGround == (int)CharacterBase::EGroundState::OnGround);
static_assert(GroundState_OnSteepGround == (int)CharacterBase::EGroundState::OnSteepGround);
static_assert(GroundState_NotSupported == (int)CharacterBase::EGroundState::NotSupported);
static_assert(GroundState_InAir == (int)CharacterBase::EGroundState::InAir);

// EBackFaceMode
static_assert(BackFaceMode_IgnoreBackFaces == (int)EBackFaceMode::IgnoreBackFaces);
static_assert(BackFaceMode_CollideWithBackFaces == (int)EBackFaceMode::CollideWithBackFaces);

// EActiveEdgeMode
static_assert(ActiveEdgeMode_CollideOnlyWithActive == (int)EActiveEdgeMode::CollideOnlyWithActive);
static_assert(ActiveEdgeMode_CollideWithAll == (int)EActiveEdgeMode::CollideWithAll);

// ECollectFacesMode
static_assert(CollectFacesMode_CollectFaces == (int)ECollectFacesMode::CollectFaces);
static_assert(CollectFacesMode_NoFaces == (int)ECollectFacesMode::NoFaces);

static_assert(sizeof(SubShapeIDPair) == sizeof(SubShapeIDPair));
static_assert(alignof(SubShapeIDPair) == alignof(SubShapeIDPair));

#ifdef DEBUG_RENDERER

// ESoftBodyConstraintColor
static_assert(SoftBodyConstraintColor_ConstraintType == (int)ESoftBodyConstraintColor::ConstraintType);
static_assert(SoftBodyConstraintColor_ConstraintGroup == (int)ESoftBodyConstraintColor::ConstraintGroup);
static_assert(SoftBodyConstraintColor_ConstraintOrder == (int)ESoftBodyConstraintColor::ConstraintOrder);

// BodyManager::EShapeColor
static_assert(BodyManager_ShapeColor_InstanceColor == (int)BodyManager::EShapeColor::InstanceColor);
static_assert(BodyManager_ShapeColor_ShapeTypeColor == (int)BodyManager::EShapeColor::ShapeTypeColor);
static_assert(BodyManager_ShapeColor_MotionTypeColor == (int)BodyManager::EShapeColor::MotionTypeColor);
static_assert(BodyManager_ShapeColor_SleepColor == (int)BodyManager::EShapeColor::SleepColor);
static_assert(BodyManager_ShapeColor_IslandColor == (int)BodyManager::EShapeColor::IslandColor);
static_assert(BodyManager_ShapeColor_MaterialColor == (int)BodyManager::EShapeColor::MaterialColor);

// DebugRenderer::ECastShadow
static_assert(DebugRenderer_CastShadow_On == (int)DebugRenderer::ECastShadow::On);
static_assert(DebugRenderer_CastShadow_Off == (int)DebugRenderer::ECastShadow::Off);

// DebugRenderer::EDrawMode
static_assert(DebugRenderer_DrawMode_Solid == (int)DebugRenderer::EDrawMode::Solid);
static_assert(DebugRenderer_DrawMode_Wireframe == (int)DebugRenderer::EDrawMode::Wireframe);

// MeshShapeSettings::EBuildQuality
static_assert(Mesh_Shape_BuildQuality_FavorRuntimePerformance == (int)MeshShapeSettings::EBuildQuality::FavorRuntimePerformance);
static_assert(Mesh_Shape_BuildQuality_FavorBuildSpeed == (int)MeshShapeSettings::EBuildQuality::FavorBuildSpeed);

// MeshShapeSettings::EBuildQuality
static_assert(TransmissionMode_Auto == (int)ETransmissionMode::Auto);
static_assert(TransmissionMode_Manual == (int)ETransmissionMode::Manual);


#endif
