//                        MIT License
//
//                  Copyright (c) 2025 Toby
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef MOSS_PHYSICS_H
#define MOSS_PHYSICS_H

/*!
 * @file Moss_Physics.h
 * @brief High-performance 2D and 3D physics simulation system powered by a modified version of Jolt Physics 5.3.0.
 *
 * The Moss Physics module provides a fast, deterministic, and multithreaded physics engine
 * designed for games, XR simulations, and large-scale environments.
 *
 * ---
 *
 * ### Core Features:
 * - **Jolt 5.3.0 Integration** — Lightweight, SIMD-accelerated, and cross-platform physics core.
 * - **2D & 3D Simulation** — Unified system supporting both 2D arcade-style and full 3D rigid-body dynamics.
 * - **Deterministic Simulation** — Ensures reproducible results across different platforms and frame rates.
 * - **Broadphase & Narrowphase Collision** — Highly optimized multi-threaded broadphase with efficient shape queries.
 * - **Continuous Collision Detection (CCD)** — Prevents tunneling for fast-moving objects.
 * - **Constraint Solver** — Handles joints, springs, and ragdolls with stable stacking and accurate motion.
 * - **Trigger & Query Support** — Overlap queries, raycasts, sweeps, and shape casts.
 * - **Material System** — Custom friction, restitution, and physical material blending.
 *
 * ---
 *
 * ### Extended Moss Features:
 * - **XR / VR Physics Support**  
 *   - Physics handles for controllers and tracked devices.  
 *   - Real-world scale simulation.  
 *   - Velocity and force-based object manipulation.  
 *   - Grabbable, throwable, and interactable physics entities.  
 *
 * - **Network-Aware Simulation (with ENet 6)**  
 *   - Snapshot and delta compression of physics states.  
 *   - Deterministic rollback for synchronized multiplayer.  
 *   - Network ownership and authority layer for replicated objects.  
 *
 * - **Debug Visualization**  
 *   - Wireframe and contact point rendering via Moss Renderer.  
 *   - Toggleable in developer builds for live debugging.  
 *
 * ---
 *
 * ### Example Usage:
 * ```cpp
 * Moss_PhysicsInit();
 *
 * PhysicsWorld* world = Moss_CreatePhysicsWorld({
 *     .gravity = Vec3(0.0f, -9.81f, 0.0f),
 *     .broadphase = BroadphaseType::DynamicAABBTree
 * });
 *
 * // Create a rigid body
 * RigidBody* box = Moss_CreateRigidBody(world, Shape_Box(Vec3(1.0f, 1.0f, 1.0f)), {0, 10, 0});
 *
 * // Step simulation
 * Moss_PhysicsStep(world, deltaTime);
 *
 * // Query collision state
 * if (Moss_IsOnGround(box)) { ... }
 * ```
 *
 * ---
 *
 * ### Advanced Capabilities:
 * - **Multithreading**  
 *   Uses job system integration to distribute collision detection, constraint solving, and island building.
 *
 * - **Scene Integration**  
 *   Physics components synchronize seamlessly with the entity system and transform hierarchy.
 *
 * - **Physics Queries**  
 *   - `Moss_Raycast(world, origin, direction, distance)`
 *   - `Moss_Sweep(world, shape, transform, direction, distance)`
 *   - `Moss_Overlap(world, shape, transform)`
 *
 * - **Dynamic Materials & Layers**  
 *   - Define collision groups and layers for efficient filtering.  
 *   - Material blending for sound, haptics, and visual feedback.  
 *
 * ---
 *
 * ### Design Goals:
 * - Scalable from mobile to high-end XR devices.
 * - Deterministic, lock-step safe for multiplayer and replays.
 * - Fully decoupled from rendering and scene systems.
 * - Predictable and extensible API for custom physics behaviors.
 *
 * ---
 *
 * ### Future Extensions:
 * - Soft-body and cloth simulation.  
 * - Fluid simulation with particle-based solvers.  
 * - GPU-accelerated broadphase (Vulkan / CUDA).  
 * - Async baking for collision meshes and static environments.  
 * - Haptic feedback integration via Moss_Haptics for physical interactions.  
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PHSICS_DEFAULT_COLLISION_TOLERANCE (1.0e-4f) // float cDefaultCollisionTolerance = 1.0e-4f
#define PHSICS_DEFAULT_PENETRATION_TOLERANCE (1.0e-4f) // float cDefaultPenetrationTolerance = 1.0e-4f
#define PHSICS_DEFAULT_CONVEX_RADIUS (0.05f) // float cDefaultConvexRadius = 0.05f
#define PHSICS_CAPSULE_PROJECTION_SLOP (0.02f) // float cCapsuleProjectionSlop = 0.02f
#define PHSICS_MAX_PHYSICS_JOBS (2048) // int cMaxPhysicsJobs = 2048
#define PHSICS_MAX_PHYSICS_BARRIERS (8) // int cMaxPhysicsBarriers = 8
#define PHSICS_INVALID_COLLISION_GROUP_ID (~0U)
#define PHSICS_INVALID_COLLISION_SUBGROUP_ID (~0U)
#define PHSICS_M_PI (3.14159265358979323846f) // To avoid collision with JPH_PI


typedef uint32_t Bool;
typedef uint32_t BodyID;
typedef uint32_t SubShapeID;
typedef uint32_t ObjectLayer;
typedef uint8_t  BroadPhaseLayer;
typedef uint32_t CollisionGroupID;
typedef uint32_t CollisionSubGroupID;
typedef uint32_t CharacterID;

/* Forward declarations */
typedef struct BroadPhaseLayerInterface				BroadPhaseLayerInterface;
typedef struct ObjectVsBroadPhaseLayerFilter		ObjectVsBroadPhaseLayerFilter;
typedef struct ObjectLayerPairFilter				ObjectLayerPairFilter;

typedef struct BroadPhaseLayerFilter				BroadPhaseLayerFilter;
typedef struct ObjectLayerFilter					ObjectLayerFilter;
typedef struct BodyFilter							BodyFilter;
typedef struct ShapeFilter							ShapeFilter;

typedef struct SimShapeFilter						SimShapeFilter;

typedef struct PhysicsStepListener					PhysicsStepListener;
typedef struct PhysicsSystem						PhysicsSystem;
typedef struct PhysicsMaterial						PhysicsMaterial;

/* ShapeSettings */
typedef struct ShapeSettings						ShapeSettings;
typedef struct ConvexShapeSettings					ConvexShapeSettings;
typedef struct SphereShapeSettings					SphereShapeSettings;
typedef struct BoxShapeSettings						BoxShapeSettings;
typedef struct PlaneShapeSettings					PlaneShapeSettings;
typedef struct TriangleShapeSettings				TriangleShapeSettings;
typedef struct CapsuleShapeSettings					CapsuleShapeSettings;
typedef struct TaperedCapsuleShapeSettings			TaperedCapsuleShapeSettings;
typedef struct CylinderShapeSettings				CylinderShapeSettings;
typedef struct TaperedCylinderShapeSettings			TaperedCylinderShapeSettings;
typedef struct ConvexHullShapeSettings				ConvexHullShapeSettings;
typedef struct CompoundShapeSettings				CompoundShapeSettings;
typedef struct StaticCompoundShapeSettings			StaticCompoundShapeSettings;
typedef struct MutableCompoundShapeSettings			MutableCompoundShapeSettings;
typedef struct MeshShapeSettings					MeshShapeSettings;
typedef struct HeightFieldShapeSettings				HeightFieldShapeSettings;
typedef struct RotatedTranslatedShapeSettings		RotatedTranslatedShapeSettings;
typedef struct ScaledShapeSettings					ScaledShapeSettings;
typedef struct OffsetCenterOfMassShapeSettings		OffsetCenterOfMassShapeSettings;
typedef struct EmptyShapeSettings					EmptyShapeSettings;

/* Shape */
typedef struct Shape								Shape;
typedef struct ConvexShape							ConvexShape;
typedef struct SphereShape							SphereShape;
typedef struct BoxShape								BoxShape;
typedef struct PlaneShape							PlaneShape;
typedef struct CapsuleShape							CapsuleShape;
typedef struct CylinderShape						CylinderShape;
typedef struct TaperedCylinderShape					TaperedCylinderShape;
typedef struct TriangleShape						TriangleShape;
typedef struct TaperedCapsuleShape					TaperedCapsuleShape;
typedef struct ConvexHullShape						ConvexHullShape;
typedef struct CompoundShape						CompoundShape;
typedef struct StaticCompoundShape					StaticCompoundShape;
typedef struct MutableCompoundShape					MutableCompoundShape;
typedef struct MeshShape							MeshShape;
typedef struct HeightFieldShape						HeightFieldShape;
typedef struct DecoratedShape						DecoratedShape;
typedef struct RotatedTranslatedShape				RotatedTranslatedShape;
typedef struct ScaledShape							ScaledShape;
typedef struct OffsetCenterOfMassShape				OffsetCenterOfMassShape;
typedef struct EmptyShape							EmptyShape;

typedef struct BodyCreationSettings					BodyCreationSettings;
typedef struct SoftBodyCreationSettings				SoftBodyCreationSettings;
typedef struct BodyInterface						BodyInterface;
typedef struct BodyLockInterface					BodyLockInterface;
typedef struct BroadPhaseQuery						BroadPhaseQuery;
typedef struct NarrowPhaseQuery						NarrowPhaseQuery;
typedef struct MotionProperties						MotionProperties;
typedef struct MassProperties						MassProperties;
typedef struct Body									Body;

typedef struct CollideShapeResult					CollideShapeResult;
typedef struct ContactListener						ContactListener;
typedef struct ContactManifold						ContactManifold;

typedef struct GroupFilter							GroupFilter;
typedef struct GroupFilterTable						GroupFilterTable;  /* Inherits GroupFilter */

/* Enums */
typedef enum PhysicsUpdateError {
	PhysicsUpdateError_None = 0,
	PhysicsUpdateError_ManifoldCacheFull = 1 << 0,
	PhysicsUpdateError_BodyPairCacheFull = 1 << 1,
	PhysicsUpdateError_ContactConstraintsFull = 1 << 2,

	_PhysicsUpdateError_Count,
	_PhysicsUpdateError_Force32 = 0x7fffffff
} PhysicsUpdateError;

typedef enum BodyType {
	BodyType_Rigid = 0,
	BodyType_Soft = 1,

	_BodyType_Count,
	_BodyType_Force32 = 0x7fffffff
} BodyType;

typedef enum MotionType {
	MotionType_Static = 0,
	MotionType_Kinematic = 1,
	MotionType_Dynamic = 2,

	_MotionType_Count,
	_MotionType_Force32 = 0x7fffffff
} MotionType;

typedef enum Activation
{
	Activation_Activate = 0,
	Activation_DontActivate = 1,

	_Activation_Count,
	_Activation_Force32 = 0x7fffffff
} Activation;

typedef enum ValidateResult {
	ValidateResult_AcceptAllContactsForThisBodyPair = 0,
	ValidateResult_AcceptContact = 1,
	ValidateResult_RejectContact = 2,
	ValidateResult_RejectAllContactsForThisBodyPair = 3,

	_ValidateResult_Count,
	_ValidateResult_Force32 = 0x7fffffff
} ValidateResult;

typedef enum ShapeType {
	ShapeType_Convex = 0,
	ShapeType_Compound = 1,
	ShapeType_Decorated = 2,
	ShapeType_Mesh = 3,
	ShapeType_HeightField = 4,
	ShapeType_SoftBody = 5,

	ShapeType_User1 = 6,
	ShapeType_User2 = 7,
	ShapeType_User3 = 8,
	ShapeType_User4 = 9,

	_ShapeType_Count,
	_ShapeType_Force32 = 0x7fffffff
} ShapeType;

typedef enum ShapeSubType {
	ShapeSubType_Sphere = 0,
	ShapeSubType_Box = 1,
	ShapeSubType_Triangle = 2,
	ShapeSubType_Capsule = 3,
	ShapeSubType_TaperedCapsule = 4,
	ShapeSubType_Cylinder = 5,
	ShapeSubType_ConvexHull = 6,
	ShapeSubType_StaticCompound = 7,
	ShapeSubType_MutableCompound = 8,
	ShapeSubType_RotatedTranslated = 9,
	ShapeSubType_Scaled = 10,
	ShapeSubType_OffsetCenterOfMass = 11,
	ShapeSubType_Mesh = 12,
	ShapeSubType_HeightField = 13,
	ShapeSubType_SoftBody = 14,

	_ShapeSubType_Count,
	_ShapeSubType_Force32 = 0x7fffffff
} ShapeSubType;

typedef enum ConstraintType {
	ConstraintType_Constraint = 0,
	ConstraintType_TwoBodyConstraint = 1,

	_ConstraintType_Count,
	_ConstraintType_Force32 = 0x7fffffff
} ConstraintType;

typedef enum ConstraintSubType {
	ConstraintSubType_Fixed = 0,
	ConstraintSubType_Point = 1,
	ConstraintSubType_Hinge = 2,
	ConstraintSubType_Slider = 3,
	ConstraintSubType_Distance = 4,
	ConstraintSubType_Cone = 5,
	ConstraintSubType_SwingTwist = 6,
	ConstraintSubType_SixDOF = 7,
	ConstraintSubType_Path = 8,
	ConstraintSubType_Vehicle = 9,
	ConstraintSubType_RackAndPinion = 10,
	ConstraintSubType_Gear = 11,
	ConstraintSubType_Pulley = 12,

	ConstraintSubType_User1 = 13,
	ConstraintSubType_User2 = 14,
	ConstraintSubType_User3 = 15,
	ConstraintSubType_User4 = 16,

	_ConstraintSubType_Count,
	_ConstraintSubType_Force32 = 0x7fffffff
} ConstraintSubType;

typedef enum ConstraintSpace {
	ConstraintSpace_LocalToBodyCOM = 0,
	ConstraintSpace_WorldSpace = 1,

	_ConstraintSpace_Count,
	_ConstraintSpace_Force32 = 0x7fffffff
} ConstraintSpace;

typedef enum MotionQuality {
	MotionQuality_Discrete = 0,
	MotionQuality_LinearCast = 1,

	_MotionQuality_Count,
	_MotionQuality_Force32 = 0x7fffffff
} MotionQuality;

typedef enum OverrideMassProperties {
	OverrideMassProperties_CalculateMassAndInertia,
	OverrideMassProperties_CalculateInertia,
	OverrideMassProperties_MassAndInertiaProvided,

	_OverrideMassProperties_Count,
	_OverrideMassProperties_Force32 = 0x7FFFFFFF
} OverrideMassProperties;

typedef enum AllowedDOFs {
	AllowedDOFs_All = 0b111111,
	AllowedDOFs_TranslationX = 0b000001,
	AllowedDOFs_TranslationY = 0b000010,
	AllowedDOFs_TranslationZ = 0b000100,
	AllowedDOFs_RotationX = 0b001000,
	AllowedDOFs_RotationY = 0b010000,
	AllowedDOFs_RotationZ = 0b100000,
	AllowedDOFs_Plane2D = AllowedDOFs_TranslationX | AllowedDOFs_TranslationY | AllowedDOFs_RotationZ,

	_AllowedDOFs_Count,
	_AllowedDOFs_Force32 = 0x7FFFFFFF
} AllowedDOFs;

typedef enum GroundState {
	GroundState_OnGround = 0,
	GroundState_OnSteepGround = 1,
	GroundState_NotSupported = 2,
	GroundState_InAir = 3,

	_GroundState_Count,
	_GroundState_Force32 = 0x7FFFFFFF
} GroundState;

typedef enum BackFaceMode {
	BackFaceMode_IgnoreBackFaces,
	BackFaceMode_CollideWithBackFaces,

	_BackFaceMode_Count,
	_BackFaceMode_Force32 = 0x7FFFFFFF
} BackFaceMode;

typedef enum ActiveEdgeMode {
	ActiveEdgeMode_CollideOnlyWithActive,
	ActiveEdgeMode_CollideWithAll,

	_ActiveEdgeMode_Count,
	_ActiveEdgeMode_Force32 = 0x7FFFFFFF
} ActiveEdgeMode;

typedef enum CollectFacesMode {
	CollectFacesMode_CollectFaces,
	CollectFacesMode_NoFaces,

	_CollectFacesMode_Count,
	_CollectFacesMode_Force32 = 0x7FFFFFFF
} CollectFacesMode;

typedef enum MotorState {
	MotorState_Off = 0,
	MotorState_Velocity = 1,
	MotorState_Position = 2,

	_MotorState_Count,
	_MotorState_Force32 = 0x7FFFFFFF
} MotorState;

typedef enum CollisionCollectorType {
	CollisionCollectorType_AllHit = 0,
	CollisionCollectorType_AllHitSorted = 1,
	CollisionCollectorType_ClosestHit = 2,
	CollisionCollectorType_AnyHit = 3,

	_CollisionCollectorType_Count,
	_CollisionCollectorType_Force32 = 0x7FFFFFFF
} CollisionCollectorType;

typedef enum SwingType {
	SwingType_Cone,
	SwingType_Pyramid,

	_SwingType_Count,
	_SwingType_Force32 = 0x7FFFFFFF
} SwingType;

typedef enum SixDOFConstraintAxis {
	SixDOFConstraintAxis_TranslationX,
	SixDOFConstraintAxis_TranslationY,
	SixDOFConstraintAxis_TranslationZ,

	SixDOFConstraintAxis_RotationX,
	SixDOFConstraintAxis_RotationY,
	SixDOFConstraintAxis_RotationZ,

	_SixDOFConstraintAxis_Num,
	_SixDOFConstraintAxis_NumTranslation = SixDOFConstraintAxis_TranslationZ + 1,
	_SixDOFConstraintAxis_Force32 = 0x7FFFFFFF
} SixDOFConstraintAxis;

typedef enum SpringMode {
	SpringMode_FrequencyAndDamping = 0,
	SpringMode_StiffnessAndDamping = 1,

	_SpringMode_Count,
	_SpringMode_Force32 = 0x7FFFFFFF
} SpringMode;

/// Defines how to color soft body constraints
typedef enum SoftBodyConstraintColor
{
	SoftBodyConstraintColor_ConstraintType,				/// Draw different types of constraints in different colors
	SoftBodyConstraintColor_ConstraintGroup,			/// Draw constraints in the same group in the same color, non-parallel group will be red
	SoftBodyConstraintColor_ConstraintOrder,			/// Draw constraints in the same group in the same color, non-parallel group will be red, and order within each group will be indicated with gradient

	_SoftBodyConstraintColor_Count,
	_SoftBodyConstraintColor_Force32 = 0x7FFFFFFF
} SoftBodyConstraintColor;

typedef enum BodyManager_ShapeColor
{
	BodyManager_ShapeColor_InstanceColor,				///< Random color per instance
	BodyManager_ShapeColor_ShapeTypeColor,				///< Convex = green, scaled = yellow, compound = orange, mesh = red
	BodyManager_ShapeColor_MotionTypeColor,			///< Static = grey, keyframed = green, dynamic = random color per instance
	BodyManager_ShapeColor_SleepColor,					///< Static = grey, keyframed = green, dynamic = yellow, sleeping = red
	BodyManager_ShapeColor_IslandColor,				///< Static = grey, active = random color per island, sleeping = light grey
	BodyManager_ShapeColor_MaterialColor,				///< Color as defined by the PhysicsMaterial of the shape

	_BodyManager_ShapeColor_Count,
	_BodyManager_ShapeColor_Force32 = 0x7FFFFFFF
} BodyManager_ShapeColor;

typedef enum DebugRenderer_CastShadow {
	DebugRenderer_CastShadow_On = 0,    ///< This shape should cast a shadow
	DebugRenderer_CastShadow_Off = 1,   ///< This shape should not cast a shadow

	_DebugRenderer_CastShadow_Count,
	_DebugRenderer_CastShadow_Force32 = 0x7FFFFFFF
} DebugRenderer_CastShadow;

typedef enum DebugRenderer_DrawMode {
	DebugRenderer_DrawMode_Solid = 0,       ///< Draw as a solid shape
	DebugRenderer_DrawMode_Wireframe = 1,   ///< Draw as wireframe

	_DebugRenderer_DrawMode_Count,
	_DebugRenderer_DrawMode_Force32 = 0x7FFFFFFF
} DebugRenderer_DrawMode;

typedef enum Mesh_Shape_BuildQuality {
	Mesh_Shape_BuildQuality_FavorRuntimePerformance = 0,
	Mesh_Shape_BuildQuality_FavorBuildSpeed = 1,

	_Mesh_Shape_BuildQuality_Count,
	_Mesh_Shape_BuildQuality_Force32 = 0x7FFFFFFF
} Mesh_Shape_BuildQuality;

typedef enum TransmissionMode {
    TransmissionMode_Auto = 0,
    TransmissionMode_Manual = 1,

    _TransmissionMode_Count,
    _TransmissionMode_Force32 = 0x7FFFFFFF
} TransmissionMode;

typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

typedef struct Vec4 {
	float x;
	float y;
	float z;
	float w;
} Vec4;

typedef struct Quat {
	float x;
	float y;
	float z;
	float w;
} Quat;

typedef struct Plane {
	Vec3 normal;
	float distance;
} Plane;

typedef struct Matrix4x4 {
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
} Matrix4x4;

#if defined(DOUBLE_PRECISION)
typedef struct RVec3 {
	double x;
	double y;
	double z;
} RVec3;

typedef struct RMatrix4x4 {
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	double m41, m42, m43, m44;
} RMatrix4x4;
#else
typedef Vec3 RVec3;
typedef Matrix4x4 RMatrix4x4;
#endif

typedef uint32_t Color;

typedef struct AABB2 {
	Vec2 min;
	Vec2 max;
} AABB2;

typedef struct AABB3 {
	Vec3 min;
	Vec3 max;
} AABB3;

typedef struct OBB2 {
	Mat44 orientation;
	Vec2 max;
} AABB2;

typedef struct OBB3 {
	Mat44 orientation;
	Vec3 max;
} AABB3;

typedef struct Triangle {
	Vec3 v1;
	Vec3 v2;
	Vec3 v3;
	uint32_t materialIndex;
} Triangle;

typedef struct IndexedTriangleNoMaterial {
	uint32_t i1;
	uint32_t i2;
	uint32_t i3;
} IndexedTriangleNoMaterial;

typedef struct IndexedTriangle {
	uint32_t i1;
	uint32_t i2;
	uint32_t i3;
	uint32_t materialIndex;
	uint32_t userData;
} IndexedTriangle;

typedef struct MassProperties {
	float mass;
	Matrix4x4 inertia;
} MassProperties;

typedef struct ContactSettings {
	float					combinedFriction;
	float					combinedRestitution;
	float					invMassScale1;
	float					invInertiaScale1;
	float					invMassScale2;
	float					invInertiaScale2;
	Bool				isSensor;
	Vec3				relativeLinearSurfaceVelocity;
	Vec3				relativeAngularSurfaceVelocity;
} ContactSettings;

typedef struct CollideSettingsBase {
	/// How active edges (edges that a moving object should bump into) are handled
	ActiveEdgeMode			activeEdgeMode/* = ActiveEdgeMode_CollideOnlyWithActive*/;

	/// If colliding faces should be collected or only the collision point
	CollectFacesMode		collectFacesMode/* = CollectFacesMode_NoFaces*/;

	/// If objects are closer than this distance, they are considered to be colliding (used for GJK) (unit: meter)
	float						collisionTolerance/* = DEFAULT_COLLISION_TOLERANCE*/;

	/// A factor that determines the accuracy of the penetration depth calculation. If the change of the squared distance is less than tolerance * current_penetration_depth^2 the algorithm will terminate. (unit: dimensionless)
	float						penetrationTolerance/* = DEFAULT_PENETRATION_TOLERANCE*/;

	/// When mActiveEdgeMode is CollideOnlyWithActive a movement direction can be provided. When hitting an inactive edge, the system will select the triangle normal as penetration depth only if it impedes the movement less than with the calculated penetration depth.
	Vec3					activeEdgeMovementDirection/* = Vec3::sZero()*/;
} CollideSettingsBase;

/* CollideShapeSettings */
typedef struct CollideShapeSettings {
	CollideSettingsBase     base;    /* Inherits CollideSettingsBase */
	/// When > 0 contacts in the vicinity of the query shape can be found. All nearest contacts that are not further away than this distance will be found (unit: meter)
	float						maxSeparationDistance/* = 0.0f*/;

	/// How backfacing triangles should be treated
	BackFaceMode			backFaceMode/* = BackFaceMode_IgnoreBackFaces*/;
} CollideShapeSettings;

/* ShapeCastSettings */
typedef struct ShapeCastSettings {
	CollideSettingsBase     base;    /* Inherits CollideSettingsBase */

	/// How backfacing triangles should be treated (should we report moving from back to front for triangle based shapes, e.g. for MeshShape/HeightFieldShape?)
	BackFaceMode			backFaceModeTriangles/* = BackFaceMode_IgnoreBackFaces*/;

	/// How backfacing convex objects should be treated (should we report starting inside an object and moving out?)
	BackFaceMode			backFaceModeConvex/* = BackFaceMode_IgnoreBackFaces*/;

	/// Indicates if we want to shrink the shape by the convex radius and then expand it again. This speeds up collision detection and gives a more accurate normal at the cost of a more 'rounded' shape.
	bool						useShrunkenShapeAndConvexRadius/* = false*/;

	/// When true, and the shape is intersecting at the beginning of the cast (fraction = 0) then this will calculate the deepest penetration point (costing additional CPU time)
	bool						returnDeepestPoint/* = false*/;
} ShapeCastSettings;

typedef struct RayCastSettings {
	/// How backfacing triangles should be treated (should we report back facing hits for triangle based shapes, e.g. MeshShape/HeightFieldShape?)
	BackFaceMode backFaceModeTriangles/* = BackFaceMode_IgnoreBackFaces*/;

	/// How backfacing convex objects should be treated (should we report back facing hits for convex shapes?)
	BackFaceMode backFaceModeConvex/* = BackFaceMode_IgnoreBackFaces*/;

	/// If convex shapes should be treated as solid. When true, a ray starting inside a convex shape will generate a hit at fraction 0.
	bool treatConvexAsSolid/* = true*/;
} RayCastSettings;

typedef struct SpringSettings {
	SpringMode mode;
	float frequencyOrStiffness;
	float damping;
} SpringSettings;

typedef struct MotorSettings {
	SpringSettings springSettings;
	float minForceLimit;
	float maxForceLimit;
	float minTorqueLimit;
	float maxTorqueLimit;
} MotorSettings;

typedef struct SubShapeIDPair {
	BodyID     Body1ID;
	SubShapeID subShapeID1;
	BodyID     Body2ID;
	SubShapeID subShapeID2;
} SubShapeIDPair;

typedef struct BroadPhaseCastResult {
	BodyID     bodyID;
	float          fraction;
} BroadPhaseCastResult;

typedef struct RayCastResult {
	BodyID     bodyID;
	float          fraction;
	SubShapeID subShapeID2;
} RayCastResult;

typedef struct CollidePointResult {
	BodyID bodyID;
	SubShapeID subShapeID2;
} CollidePointResult;

typedef struct CollideShapeResult {
	Vec3		contactPointOn1;
	Vec3		contactPointOn2;
	Vec3		penetrationAxis;
	float			penetrationDepth;
	SubShapeID	subShapeID1;
	SubShapeID	subShapeID2;
	BodyID		bodyID2;
	uint32_t		shape1FaceCount;
	Vec3*		shape1Faces;
	uint32_t		shape2FaceCount;
	Vec3*		shape2Faces;
} CollideShapeResult;

typedef struct ShapeCastResult {
	Vec3           contactPointOn1;
	Vec3           contactPointOn2;
	Vec3           penetrationAxis;
	float              penetrationDepth;
	SubShapeID     subShapeID1;
	SubShapeID     subShapeID2;
	BodyID         bodyID2;
	float              fraction;
	bool			   isBackFaceHit;
} ShapeCastResult;

typedef struct DrawSettings {
	bool						drawGetSupportFunction;				///< Draw the GetSupport() function, used for convex collision detection
	bool						drawSupportDirection;				///< When drawing the support function, also draw which direction mapped to a specific support point
	bool						drawGetSupportingFace;				///< Draw the faces that were found colliding during collision detection
	bool						drawShape;							///< Draw the shapes of all bodies
	bool						drawShapeWireframe;					///< When mDrawShape is true and this is true, the shapes will be drawn in wireframe instead of solid.
	BodyManager_ShapeColor	drawShapeColor;                     ///< Coloring scheme to use for shapes
	bool						drawBoundingBox;					///< Draw a bounding box per body
	bool						drawCenterOfMassTransform;			///< Draw the center of mass for each body
	bool						drawWorldTransform;					///< Draw the world transform (which may differ from its center of mass) of each body
	bool						drawVelocity;						///< Draw the velocity vector for each body
	bool						drawMassAndInertia;					///< Draw the mass and inertia (as the box equivalent) for each body
	bool						drawSleepStats;						///< Draw stats regarding the sleeping algorithm of each body
	bool						drawSoftBodyVertices;				///< Draw the vertices of soft bodies
	bool						drawSoftBodyVertexVelocities;		///< Draw the velocities of the vertices of soft bodies
	bool						drawSoftBodyEdgeConstraints;		///< Draw the edge constraints of soft bodies
	bool						drawSoftBodyBendConstraints;		///< Draw the bend constraints of soft bodies
	bool						drawSoftBodyVolumeConstraints;		///< Draw the volume constraints of soft bodies
	bool						drawSoftBodySkinConstraints;		///< Draw the skin constraints of soft bodies
	bool						drawSoftBodyLRAConstraints;	        ///< Draw the LRA constraints of soft bodies
	bool						drawSoftBodyPredictedBounds;		///< Draw the predicted bounds of soft bodies
	SoftBodyConstraintColor	drawSoftBodyConstraintColor;        ///< Coloring scheme to use for soft body constraints
} DrawSettings;

typedef struct SupportingFace {
    uint32_t count;
    Vec3 vertices[32];
} SupportingFace;

typedef struct CollisionGroup {
	const GroupFilter*	groupFilter;
	CollisionGroupID	groupID;
	CollisionSubGroupID	subGroupID;
} CollisionGroup;

typedef void CastRayResultCallback(void* context, const RayCastResult* result);
typedef void RayCastBodyResultCallback(void* context, const BroadPhaseCastResult* result);
typedef void CollideShapeBodyResultCallback(void* context, const BodyID result);
typedef void CollidePointResultCallback(void* context, const CollidePointResult* result);
typedef void CollideShapeResultCallback(void* context, const CollideShapeResult* result);
typedef void CastShapeResultCallback(void* context, const ShapeCastResult* result);

typedef float CastRayCollectorCallback(void* context, const RayCastResult* result);
typedef float RayCastBodyCollectorCallback(void* context, const BroadPhaseCastResult* result);
typedef float CollideShapeBodyCollectorCallback(void* context, const BodyID result);
typedef float CollidePointCollectorCallback(void* context, const CollidePointResult* result);
typedef float CollideShapeCollectorCallback(void* context, const CollideShapeResult* result);
typedef float CastShapeCollectorCallback(void* context, const ShapeCastResult* result);

typedef struct CollisionEstimationResultImpulse {
	float	contactImpulse;
	float	frictionImpulse1;
	float	frictionImpulse2;
} CollisionEstimationResultImpulse;

typedef struct CollisionEstimationResult {
	Vec3								linearVelocity1;
	Vec3								angularVelocity1;
	Vec3								linearVelocity2;
	Vec3								angularVelocity2;

	Vec3								tangent1;
	Vec3								tangent2;

	uint32_t								impulseCount;
	CollisionEstimationResultImpulse*	impulses;
} CollisionEstimationResult;

typedef struct BodyActivationListener           BodyActivationListener;
typedef struct BodyDrawFilter                   BodyDrawFilter;

typedef struct SharedMutex                      SharedMutex;

typedef struct DebugRenderer                    DebugRenderer;

/* Constraint */
typedef struct Constraint                       Constraint;
typedef struct TwoBodyConstraint                TwoBodyConstraint;
typedef struct FixedConstraint                  FixedConstraint;
typedef struct DistanceConstraint               DistanceConstraint;
typedef struct PointConstraint                  PointConstraint;
typedef struct HingeConstraint                  HingeConstraint;
typedef struct SliderConstraint                 SliderConstraint;
typedef struct ConeConstraint                   ConeConstraint;
typedef struct SwingTwistConstraint             SwingTwistConstraint;
typedef struct SixDOFConstraint				    SixDOFConstraint;
typedef struct GearConstraint				    GearConstraint;

/* Character, CharacterVirtual */
typedef struct CharacterBase					CharacterBase;
typedef struct Character						Character;  /* Inherits CharacterBase */
typedef struct CharacterVirtual                 CharacterVirtual;  /* Inherits CharacterBase */
typedef struct CharacterContactListener			CharacterContactListener;
typedef struct CharacterVsCharacterCollision	CharacterVsCharacterCollision;

/* Skeleton/Ragdoll */
typedef struct Skeleton							Skeleton;
typedef struct RagdollSettings					RagdollSettings;
typedef struct Ragdoll							Ragdoll;

typedef struct ConstraintSettings {
	bool						enabled;
	uint32_t					constraintPriority;
	uint32_t					numVelocityStepsOverride;
	uint32_t					numPositionStepsOverride;
	float						drawConstraintSize;
	uint64_t					userData;
} ConstraintSettings;

typedef struct FixedConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	bool						autoDetectPoint;
	RVec3					point1;
	Vec3					axisX1;
	Vec3					axisY1;
	RVec3					point2;
	Vec3					axisX2;
	Vec3					axisY2;
} FixedConstraintSettings;

typedef struct DistanceConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	RVec3					point1;
	RVec3					point2;
	float						minDistance;
	float						maxDistance;
	SpringSettings			limitsSpringSettings;
} DistanceConstraintSettings;

typedef struct PointConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	RVec3					point1;
	RVec3					point2;
} PointConstraintSettings;

typedef struct HingeConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	RVec3					point1;
	Vec3					hingeAxis1;
	Vec3					normalAxis1;
	RVec3					point2;
	Vec3					hingeAxis2;
	Vec3					normalAxis2;
	float						limitsMin;
	float						limitsMax;
	SpringSettings			limitsSpringSettings;
	float						maxFrictionTorque;
	MotorSettings			motorSettings;
} HingeConstraintSettings;

typedef struct SliderConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	bool						autoDetectPoint;
	RVec3					point1;
	Vec3					sliderAxis1;
	Vec3					normalAxis1;
	RVec3					point2;
	Vec3					sliderAxis2;
	Vec3					normalAxis2;
	float						limitsMin;
	float						limitsMax;
	SpringSettings			limitsSpringSettings;
	float						maxFrictionForce;
	MotorSettings			motorSettings;
} SliderConstraintSettings;

typedef struct ConeConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	RVec3					point1;
	Vec3					twistAxis1;
	RVec3					point2;
	Vec3					twistAxis2;
	float						halfConeAngle;
} ConeConstraintSettings;

typedef struct SwingTwistConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	RVec3					position1;
	Vec3					twistAxis1;
	Vec3					planeAxis1;
	RVec3					position2;
	Vec3					twistAxis2;
	Vec3					planeAxis2;
	SwingType				swingType;
	float						normalHalfConeAngle;
	float						planeHalfConeAngle;
	float						twistMinAngle;
	float						twistMaxAngle;
	float						maxFrictionTorque;
	MotorSettings			swingMotorSettings;
	MotorSettings			twistMotorSettings;
} SwingTwistConstraintSettings;

typedef struct SixDOFConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	RVec3					position1;
	Vec3					axisX1;
	Vec3					axisY1;
	RVec3					position2;
	Vec3					axisX2;
	Vec3					axisY2;
	float						maxFriction[_SixDOFConstraintAxis_Num];
	SwingType				swingType;
	float						limitMin[_SixDOFConstraintAxis_Num];
	float						limitMax[_SixDOFConstraintAxis_Num];

	SpringSettings			limitsSpringSettings[_SixDOFConstraintAxis_NumTranslation];
	MotorSettings			motorSettings[_SixDOFConstraintAxis_Num];
} SixDOFConstraintSettings;

typedef struct GearConstraintSettings {
	ConstraintSettings		base;    /* Inherits ConstraintSettings */

	ConstraintSpace			space;
	Vec3					hingeAxis1;
	Vec3					hingeAxis2;
	float						ratio;
} GearConstraintSettings;

typedef struct BodyLockRead {
	const BodyLockInterface* lockInterface;
	SharedMutex* mutex;
	const Body* body;
} BodyLockRead;

typedef struct BodyLockWrite {
	const BodyLockInterface* lockInterface;
	SharedMutex* mutex;
	Body* body;
} BodyLockWrite;

typedef struct BodyLockMultiRead BodyLockMultiRead;
typedef struct BodyLockMultiWrite BodyLockMultiWrite;

typedef struct ExtendedUpdateSettings {
	Vec3	stickToFloorStepDown;
	Vec3	walkStairsStepUp;
	float		walkStairsMinStepForward;
	float		walkStairsStepForwardTest;
	float		walkStairsCosAngleForwardContact;
	Vec3	walkStairsStepDownExtra;
} ExtendedUpdateSettings;

typedef struct CharacterBaseSettings {
	Vec3 up;
	Plane supportingVolume;
	float maxSlopeAngle;
	bool enhancedInternalEdgeRemoval;
	const Shape* shape;
} CharacterBaseSettings;

/* Character */
typedef struct CharacterSettings {
	CharacterBaseSettings       base;    /* Inherits CharacterBaseSettings */
	ObjectLayer					layer;
	float							mass;
	float							friction;
	float							gravityFactor;
	AllowedDOFs                 allowedDOFs;
} CharacterSettings;

/* CharacterVirtual */
typedef struct CharacterVirtualSettings {
	CharacterBaseSettings           base;    /* Inherits CharacterBaseSettings */
	CharacterID						ID;
	float								mass;
	float								maxStrength;
	Vec3							shapeOffset;
	BackFaceMode					backFaceMode;
	float								predictiveContactDistance;
	uint32_t							maxCollisionIterations;
	uint32_t							maxConstraintIterations;
	float								minTimeRemaining;
	float								collisionTolerance;
	float								characterPadding;
	uint32_t							maxNumHits;
	float								hitReductionCosMaxAngle;
	float								penetrationRecoverySpeed;
	const Shape*					innerBodyShape;
	BodyID							innerBodyIDOverride;
	ObjectLayer						innerBodyLayer;
} CharacterVirtualSettings;

typedef struct CharacterContactSettings {
	bool canPushCharacter;
	bool canReceiveImpulses;
} CharacterContactSettings;

typedef struct CharacterVirtualContact {
	uint64_t						hash;
	BodyID						bodyB;
	CharacterID					characterIDB;
	SubShapeID					subShapeIDB;
	RVec3						position;
	Vec3						linearVelocity;
	Vec3						contactNormal;
	Vec3						surfaceNormal;
	float							distance;
	float							fraction;
	MotionType					motionTypeB;
	bool							isSensorB;
	const CharacterVirtual*		characterB;
	uint64_t						userData;
	const PhysicsMaterial*		material;
	bool							hadCollision;
	bool							wasDiscarded;
	bool							canPushCharacter;
} CharacterVirtualContact;

typedef void(API_CALL* TraceFunc)(const char* message);
typedef bool(API_CALL* AssertFailureFunc)(const char* expression, const char* message, const char* file, uint32_t line);

typedef void JobFunction(void* arg);
typedef void QueueJobCallback(void* context, JobFunction* job, void* arg);
typedef void QueueJobsCallback(void* context, JobFunction* job, void** args, uint32_t count);

typedef struct JobSystemThreadPoolConfig {
	uint32_t maxJobs;
	uint32_t maxBarriers;
	int32_t numThreads;
} JobSystemThreadPoolConfig;

typedef struct JobSystemConfig {
	void* context;
	QueueJobCallback* queueJob;
	QueueJobsCallback* queueJobs;
	uint32_t maxConcurrency;
	uint32_t maxBarriers;
} JobSystemConfig;

typedef struct JobSystem JobSystem;

MOSS_API JobSystem* JobSystemThreadPool_Create(const JobSystemThreadPoolConfig* config);
MOSS_API JobSystem* JobSystemCallback_Create(const JobSystemConfig* config);
MOSS_API void JobSystem_Destroy(JobSystem* jobSystem);

MOSS_API bool Init(void);
MOSS_API void Shutdown(void);
MOSS_API void SetTraceHandler(TraceFunc handler);
MOSS_API void SetAssertFailureHandler(AssertFailureFunc handler);

/* Structs free members */
MOSS_API void CollideShapeResult_FreeMembers(CollideShapeResult* result);
MOSS_API void CollisionEstimationResult_FreeMembers(CollisionEstimationResult* result);

/* BroadPhaseLayerInterface */
MOSS_API BroadPhaseLayerInterface* BroadPhaseLayerInterfaceMask_Create(uint32_t numBroadPhaseLayers);
MOSS_API void BroadPhaseLayerInterfaceMask_ConfigureLayer(BroadPhaseLayerInterface* bpInterface, BroadPhaseLayer broadPhaseLayer, uint32_t groupsToInclude, uint32_t groupsToExclude);

MOSS_API BroadPhaseLayerInterface* BroadPhaseLayerInterfaceTable_Create(uint32_t numObjectLayers, uint32_t numBroadPhaseLayers);
MOSS_API void BroadPhaseLayerInterfaceTable_MapObjectToBroadPhaseLayer(BroadPhaseLayerInterface* bpInterface, ObjectLayer objectLayer, BroadPhaseLayer broadPhaseLayer);

/* ObjectLayerPairFilter */
MOSS_API ObjectLayerPairFilter* ObjectLayerPairFilterMask_Create(void);
MOSS_API ObjectLayer ObjectLayerPairFilterMask_GetObjectLayer(uint32_t group, uint32_t mask);
MOSS_API uint32_t ObjectLayerPairFilterMask_GetGroup(ObjectLayer layer);
MOSS_API uint32_t ObjectLayerPairFilterMask_GetMask(ObjectLayer layer);

MOSS_API ObjectLayerPairFilter* ObjectLayerPairFilterTable_Create(uint32_t numObjectLayers);
MOSS_API void ObjectLayerPairFilterTable_DisableCollision(ObjectLayerPairFilter* objectFilter, ObjectLayer layer1, ObjectLayer layer2);
MOSS_API void ObjectLayerPairFilterTable_EnableCollision(ObjectLayerPairFilter* objectFilter, ObjectLayer layer1, ObjectLayer layer2);
MOSS_API bool ObjectLayerPairFilterTable_ShouldCollide(ObjectLayerPairFilter* objectFilter, ObjectLayer layer1, ObjectLayer layer2);

/* ObjectVsBroadPhaseLayerFilter */
MOSS_API ObjectVsBroadPhaseLayerFilter* ObjectVsBroadPhaseLayerFilterMask_Create(const BroadPhaseLayerInterface* broadPhaseLayerInterface);

MOSS_API ObjectVsBroadPhaseLayerFilter* ObjectVsBroadPhaseLayerFilterTable_Create(
	BroadPhaseLayerInterface* broadPhaseLayerInterface, uint32_t numBroadPhaseLayers,
	ObjectLayerPairFilter* objectLayerPairFilter, uint32_t numObjectLayers);

MOSS_API void DrawSettings_InitDefault(DrawSettings* settings);

/* PhysicsSystem */
typedef struct PhysicsSystemSettings {
	uint32_t maxBodies; /* 10240 */
	uint32_t numBodyMutexes; /* 0 */
	uint32_t maxBodyPairs; /* 65536 */
	uint32_t maxContactConstraints; /* 10240 */
	uint32_t _padding;
	BroadPhaseLayerInterface* broadPhaseLayerInterface;
	ObjectLayerPairFilter* objectLayerPairFilter;
	ObjectVsBroadPhaseLayerFilter* objectVsBroadPhaseLayerFilter;
} PhysicsSystemSettings;

typedef struct PhysicsSettings {
	int maxInFlightBodyPairs;
	int stepListenersBatchSize;
	int stepListenerBatchesPerJob;
	float baumgarte;
	float speculativeContactDistance;
	float penetrationSlop;
	float linearCastThreshold;
	float linearCastMaxPenetration;
	float manifoldTolerance;
	float maxPenetrationDistance;
	float bodyPairCacheMaxDeltaPositionSq;
	float bodyPairCacheCosMaxDeltaRotationDiv2;
	float contactNormalCosMaxDeltaRotation;
	float contactPointPreserveLambdaMaxDistSq;
	uint32_t numVelocitySteps;
	uint32_t numPositionSteps;
	float minVelocityForRestitution;
	float timeBeforeSleep;
	float pointVelocitySleepThreshold;
	bool deterministicSimulation;
	bool constraintWarmStart;
	bool useBodyPairContactCache;
	bool useManifoldReduction;
	bool useLargeIslandSplitter;
	bool allowSleeping;
	bool checkActiveEdges;
} PhysicsSettings;

MOSS_API PhysicsSystem* PhysicsSystem_Create(const PhysicsSystemSettings* settings);
MOSS_API void PhysicsSystem_Destroy(PhysicsSystem* system);

MOSS_API void PhysicsSystem_SetPhysicsSettings(PhysicsSystem* system, PhysicsSettings* settings);
MOSS_API void PhysicsSystem_GetPhysicsSettings(PhysicsSystem* system, PhysicsSettings* result);

MOSS_API void PhysicsSystem_OptimizeBroadPhase(PhysicsSystem* system);
MOSS_API PhysicsUpdateError PhysicsSystem_Update(PhysicsSystem* system, float deltaTime, int collisionSteps, JobSystem* jobSystem);

MOSS_API BodyInterface* PhysicsSystem_GetBodyInterface(PhysicsSystem* system);
MOSS_API BodyInterface* PhysicsSystem_GetBodyInterfaceNoLock(PhysicsSystem* system);

MOSS_API const BodyLockInterface* PhysicsSystem_GetBodyLockInterface(const PhysicsSystem* system);
MOSS_API const BodyLockInterface* PhysicsSystem_GetBodyLockInterfaceNoLock(const PhysicsSystem* system);

MOSS_API const BroadPhaseQuery* PhysicsSystem_GetBroadPhaseQuery(const PhysicsSystem* system);

MOSS_API const NarrowPhaseQuery* PhysicsSystem_GetNarrowPhaseQuery(const PhysicsSystem* system);
MOSS_API const NarrowPhaseQuery* PhysicsSystem_GetNarrowPhaseQueryNoLock(const PhysicsSystem* system);

MOSS_API void PhysicsSystem_SetContactListener(PhysicsSystem* system, ContactListener* listener);
MOSS_API void PhysicsSystem_SetBodyActivationListener(PhysicsSystem* system, BodyActivationListener* listener);
MOSS_API void PhysicsSystem_SetSimShapeFilter(PhysicsSystem* system, const SimShapeFilter* filter);

MOSS_API bool PhysicsSystem_WereBodiesInContact(const PhysicsSystem* system, BodyID body1, BodyID body2);

MOSS_API uint32_t PhysicsSystem_GetNumBodies(const PhysicsSystem* system);
MOSS_API uint32_t PhysicsSystem_GetNumActiveBodies(const PhysicsSystem* system, BodyType type);
MOSS_API uint32_t PhysicsSystem_GetMaxBodies(const PhysicsSystem* system);
MOSS_API uint32_t PhysicsSystem_GetNumConstraints(const PhysicsSystem* system);

MOSS_API void PhysicsSystem_SetGravity(PhysicsSystem* system, const Vec3* value);
MOSS_API void PhysicsSystem_GetGravity(PhysicsSystem* system, Vec3* result);

MOSS_API void PhysicsSystem_AddConstraint(PhysicsSystem* system, Constraint* constraint);
MOSS_API void PhysicsSystem_RemoveConstraint(PhysicsSystem* system, Constraint* constraint);

MOSS_API void PhysicsSystem_AddConstraints(PhysicsSystem* system, Constraint** constraints, uint32_t count);
MOSS_API void PhysicsSystem_RemoveConstraints(PhysicsSystem* system, Constraint** constraints, uint32_t count);

MOSS_API void PhysicsSystem_AddStepListener(PhysicsSystem* system, PhysicsStepListener* listener);
MOSS_API void PhysicsSystem_RemoveStepListener(PhysicsSystem* system, PhysicsStepListener* listener);

MOSS_API void PhysicsSystem_GetBodies(const PhysicsSystem* system, BodyID* ids, uint32_t count);
MOSS_API void PhysicsSystem_GetConstraints(const PhysicsSystem* system, const Constraint** constraints, uint32_t count);

MOSS_API void PhysicsSystem_DrawBodies(PhysicsSystem* system, const DrawSettings* settings, DebugRenderer* renderer, const BodyDrawFilter* bodyFilter /* = nullptr */);
MOSS_API void PhysicsSystem_DrawConstraints(PhysicsSystem* system, DebugRenderer* renderer);
MOSS_API void PhysicsSystem_DrawConstraintLimits(PhysicsSystem* system, DebugRenderer* renderer);
MOSS_API void PhysicsSystem_DrawConstraintReferenceFrame(PhysicsSystem* system, DebugRenderer* renderer);

/* PhysicsStepListener */
typedef struct PhysicsStepListenerContext {
	float					deltaTime;
	Bool				isFirstStep;
	Bool				isLastStep;
	PhysicsSystem*		physicsSystem;
} PhysicsStepListenerContext;


typedef struct PhysicsStepListener_Procs {
	void(API_CALL* OnStep)(void* userData, const PhysicsStepListenerContext* context);
} PhysicsStepListener_Procs;

MOSS_API void PhysicsStepListener_SetProcs(const PhysicsStepListener_Procs* procs);
MOSS_API PhysicsStepListener* PhysicsStepListener_Create(void* userData);
MOSS_API void PhysicsStepListener_Destroy(PhysicsStepListener* listener);

/* Math */
MOSS_API float Math_Sin(float value);
MOSS_API float Math_Cos(float value);

MOSS_API void Quat_FromTo(const Vec3* from, const Vec3* to, Quat* quat);
MOSS_API void Quat_GetAxisAngle(const Quat* quat, Vec3* outAxis, float* outAngle);
MOSS_API void Quat_GetEulerAngles(const Quat* quat, Vec3* result);
MOSS_API void Quat_RotateAxisX(const Quat* quat, Vec3* result);
MOSS_API void Quat_RotateAxisY(const Quat* quat, Vec3* result);
MOSS_API void Quat_RotateAxisZ(const Quat* quat, Vec3* result);
MOSS_API void Quat_Inversed(const Quat* quat, Quat* result);
MOSS_API void Quat_GetPerpendicular(const Quat* quat, Quat* result);
MOSS_API float Quat_GetRotationAngle(const Quat* quat, const Vec3* axis);
MOSS_API void Quat_FromEulerAngles(const Vec3* angles, Quat* result);

MOSS_API void Quat_Add(const Quat* q1, const Quat* q2, Quat* result);
MOSS_API void Quat_Subtract(const Quat* q1, const Quat* q2, Quat* result);
MOSS_API void Quat_Multiply(const Quat* q1, const Quat* q2, Quat* result);
MOSS_API void Quat_MultiplyScalar(const Quat* q, float scalar, Quat* result);
MOSS_API void Quat_DivideScalar(const Quat* q, float scalar, Quat* result);
MOSS_API void Quat_Dot(const Quat* q1, const Quat* q2, float* result);

MOSS_API void Quat_Conjugated(const Quat* quat, Quat* result);
MOSS_API void Quat_GetTwist(const Quat* quat, const Vec3* axis, Quat* result);
MOSS_API void Quat_GetSwingTwist(const Quat* quat, Quat* outSwing, Quat* outTwist);
MOSS_API void Quat_Lerp(const Quat* from, const Quat* to, float fraction, Quat* result);
MOSS_API void Quat_Slerp(const Quat* from, const Quat* to, float fraction, Quat* result);
MOSS_API void Quat_Rotate(const Quat* quat, const Vec3* vec, Vec3* result);
MOSS_API void Quat_InverseRotate(const Quat* quat, const Vec3* vec, Vec3* result);

MOSS_API void Vec3_AxisX(Vec3* result);
MOSS_API void Vec3_AxisY(Vec3* result);
MOSS_API void Vec3_AxisZ(Vec3* result);
MOSS_API bool Vec3_IsClose(const Vec3* v1, const Vec3* v2, float maxDistSq);
MOSS_API bool Vec3_IsNearZero(const Vec3* v, float maxDistSq);
MOSS_API bool Vec3_IsNormalized(const Vec3* v, float tolerance);
MOSS_API bool Vec3_IsNaN(const Vec3* v);

MOSS_API void Vec3_Negate(const Vec3* v, Vec3* result);
MOSS_API void Vec3_Normalized(const Vec3* v, Vec3* result);
MOSS_API void Vec3_Cross(const Vec3* v1, const Vec3* v2, Vec3* result);
MOSS_API void Vec3_Abs(const Vec3* v, Vec3* result);

MOSS_API float Vec3_Length(const Vec3* v);
MOSS_API float Vec3_LengthSquared(const Vec3* v);

MOSS_API void Vec3_DotProduct(const Vec3* v1, const Vec3* v2, float* result);
MOSS_API void Vec3_Normalize(const Vec3* v, Vec3* result);

MOSS_API void Vec3_Add(const Vec3* v1, const Vec3* v2, Vec3* result);
MOSS_API void Vec3_Subtract(const Vec3* v1, const Vec3* v2, Vec3* result);
MOSS_API void Vec3_Multiply(const Vec3* v1, const Vec3* v2, Vec3* result);
MOSS_API void Vec3_MultiplyScalar(const Vec3* v, float scalar, Vec3* result);
MOSS_API void Vec3_MultiplyMatrix(const Matrix4x4* left, const Vec3* right, Vec3* result);

MOSS_API void Vec3_Divide(const Vec3* v1, const Vec3* v2, Vec3* result);
MOSS_API void Vec3_DivideScalar(const Vec3* v, float scalar, Vec3* result);

MOSS_API void Matrix4x4_Add(const Matrix4x4* m1, const Matrix4x4* m2, Matrix4x4* result);
MOSS_API void Matrix4x4_Subtract(const Matrix4x4* m1, const Matrix4x4* m2, Matrix4x4* result);
MOSS_API void Matrix4x4_Multiply(const Matrix4x4* m1, const Matrix4x4* m2, Matrix4x4* result);
MOSS_API void Matrix4x4_MultiplyScalar(const Matrix4x4* m, float scalar, Matrix4x4* result);

MOSS_API void Matrix4x4_Zero(Matrix4x4* result);
MOSS_API void Matrix4x4_Identity(Matrix4x4* result);
MOSS_API void Matrix4x4_Rotation(Matrix4x4* result, const Quat* rotation);
MOSS_API void Matrix4x4_Rotation2(Matrix4x4* result, const Vec3* axis, float angle);
MOSS_API void Matrix4x4_Translation(Matrix4x4* result, const Vec3* translation);
MOSS_API void Matrix4x4_RotationTranslation(Matrix4x4* result, const Quat* rotation, const Vec3* translation);
MOSS_API void Matrix4x4_InverseRotationTranslation(Matrix4x4* result, const Quat* rotation, const Vec3* translation);
MOSS_API void Matrix4x4_Scale(Matrix4x4* result, const Vec3* scale);
MOSS_API void Matrix4x4_Inversed(const Matrix4x4* m, Matrix4x4* result);
MOSS_API void Matrix4x4_Transposed(const Matrix4x4* m, Matrix4x4* result);

MOSS_API void RMatrix4x4_Zero(RMatrix4x4* result);
MOSS_API void RMatrix4x4_Identity(RMatrix4x4* result);
MOSS_API void RMatrix4x4_Rotation(RMatrix4x4* result, const Quat* rotation);
MOSS_API void RMatrix4x4_Translation(RMatrix4x4* result, const RVec3* translation);
MOSS_API void RMatrix4x4_RotationTranslation(RMatrix4x4* result, const Quat* rotation, const RVec3* translation);
MOSS_API void RMatrix4x4_InverseRotationTranslation(RMatrix4x4* result, const Quat* rotation, const RVec3* translation);
MOSS_API void RMatrix4x4_Scale(RMatrix4x4* result, const Vec3* scale);
MOSS_API void RMatrix4x4_Inversed(const RMatrix4x4* m, RMatrix4x4* result);

MOSS_API void Matrix4x4_GetAxisX(const Matrix4x4* matrix, Vec3* result);
MOSS_API void Matrix4x4_GetAxisY(const Matrix4x4* matrix, Vec3* result);
MOSS_API void Matrix4x4_GetAxisZ(const Matrix4x4* matrix, Vec3* result);
MOSS_API void Matrix4x4_GetTranslation(const Matrix4x4* matrix, Vec3* result);
MOSS_API void Matrix4x4_GetQuaternion(const Matrix4x4* matrix, Quat* result);

/* Material */
MOSS_API PhysicsMaterial* PhysicsMaterial_Create(const char* name, uint32_t color);
MOSS_API void PhysicsMaterial_Destroy(PhysicsMaterial* material);
MOSS_API const char* PhysicsMaterial_GetDebugName(const PhysicsMaterial* material);
MOSS_API uint32_t PhysicsMaterial_GetDebugColor(const PhysicsMaterial* material);

/* GroupFilter/GroupFilterTable */
MOSS_API void GroupFilter_Destroy(GroupFilter* groupFilter);
MOSS_API bool GroupFilter_CanCollide(GroupFilter* groupFilter, const CollisionGroup* group1, const CollisionGroup* group2);

MOSS_API GroupFilterTable* GroupFilterTable_Create(uint32_t numSubGroups/* = 0*/);
MOSS_API void GroupFilterTable_DisableCollision(GroupFilterTable* table, CollisionSubGroupID subGroup1, CollisionSubGroupID subGroup2);
MOSS_API void GroupFilterTable_EnableCollision(GroupFilterTable* table, CollisionSubGroupID subGroup1, CollisionSubGroupID subGroup2);
MOSS_API bool GroupFilterTable_IsCollisionEnabled(GroupFilterTable* table, CollisionSubGroupID subGroup1, CollisionSubGroupID subGroup2);

/* ShapeSettings */
MOSS_API void ShapeSettings_Destroy(ShapeSettings* settings);
MOSS_API uint64_t ShapeSettings_GetUserData(const ShapeSettings* settings);
MOSS_API void ShapeSettings_SetUserData(ShapeSettings* settings, uint64_t userData);

/* Shape */
MOSS_API void Shape_Destroy(Shape* shape);
MOSS_API ShapeType Shape_GetType(const Shape* shape);
MOSS_API ShapeSubType Shape_GetSubType(const Shape* shape);
MOSS_API uint64_t Shape_GetUserData(const Shape* shape);
MOSS_API void Shape_SetUserData(Shape* shape, uint64_t userData);
MOSS_API bool Shape_MustBeStatic(const Shape* shape);
MOSS_API void Shape_GetCenterOfMass(const Shape* shape, Vec3* result);
MOSS_API void Shape_GetLocalBounds(const Shape* shape, AABB3* result);
MOSS_API uint32_t Shape_GetSubShapeIDBitsRecursive(const Shape* shape);
MOSS_API void Shape_GetWorldSpaceBounds(const Shape* shape, RMatrix4x4* centerOfMassTransform, Vec3* scale, AABB3* result);
MOSS_API float Shape_GetInnerRadius(const Shape* shape);
MOSS_API void Shape_GetMassProperties(const Shape* shape, MassProperties* result);
MOSS_API const Shape* Shape_GetLeafShape(const Shape* shape, SubShapeID subShapeID, SubShapeID* remainder);
MOSS_API const PhysicsMaterial* Shape_GetMaterial(const Shape* shape, SubShapeID subShapeID);
MOSS_API void Shape_GetSurfaceNormal(const Shape* shape, SubShapeID subShapeID, Vec3* localPosition, Vec3* normal);
MOSS_API void Shape_GetSupportingFace(const Shape* shape, const SubShapeID subShapeID, const Vec3* direction, const Vec3* scale, const Matrix4x4* centerOfMassTransform, SupportingFace* outVertices);
MOSS_API float Shape_GetVolume(const Shape* shape);
MOSS_API bool Shape_IsValidScale(const Shape* shape, const Vec3* scale);
MOSS_API void Shape_MakeScaleValid(const Shape* shape, const Vec3* scale, Vec3* result);
MOSS_API Shape* Shape_ScaleShape(const Shape* shape, const Vec3* scale);
MOSS_API bool Shape_CastRay(const Shape* shape, const Vec3* origin, const Vec3* direction, RayCastResult* hit);
MOSS_API bool Shape_CastRay2(const Shape* shape, const Vec3* origin, const Vec3* direction, const RayCastSettings* rayCastSettings, CollisionCollectorType collectorType, CastRayResultCallback* callback, void* userData, const ShapeFilter* shapeFilter);
MOSS_API bool Shape_CollidePoint(const Shape* shape, const Vec3* point, const ShapeFilter* shapeFilter);
MOSS_API bool Shape_CollidePoint2(const Shape* shape, const Vec3* point, CollisionCollectorType collectorType, CollidePointResultCallback* callback, void* userData, const ShapeFilter* shapeFilter);

/* ConvexShape */
MOSS_API float ConvexShapeSettings_GetDensity(const ConvexShapeSettings* shape);
MOSS_API void ConvexShapeSettings_SetDensity(ConvexShapeSettings* shape, float value);
MOSS_API float ConvexShape_GetDensity(const ConvexShape* shape);
MOSS_API void ConvexShape_SetDensity(ConvexShape* shape, float inDensity);

/* BoxShape */
MOSS_API BoxShapeSettings* BoxShapeSettings_Create(const Vec3* halfExtent, float convexRadius);
MOSS_API BoxShape* BoxShapeSettings_CreateShape(const BoxShapeSettings* settings);

MOSS_API BoxShape* BoxShape_Create(const Vec3* halfExtent, float convexRadius);
MOSS_API void BoxShape_GetHalfExtent(const BoxShape* shape, Vec3* halfExtent);
MOSS_API float BoxShape_GetConvexRadius(const BoxShape* shape);

/* SphereShape */
MOSS_API SphereShapeSettings* SphereShapeSettings_Create(float radius);
MOSS_API SphereShape* SphereShapeSettings_CreateShape(const SphereShapeSettings* settings);

MOSS_API float SphereShapeSettings_GetRadius(const SphereShapeSettings* settings);
MOSS_API void SphereShapeSettings_SetRadius(SphereShapeSettings* settings, float radius);
MOSS_API SphereShape* SphereShape_Create(float radius);
MOSS_API float SphereShape_GetRadius(const SphereShape* shape);

/* PlaneShape */
MOSS_API PlaneShapeSettings* PlaneShapeSettings_Create(const Plane* plane, const PhysicsMaterial* material, float halfExtent);
MOSS_API PlaneShape* PlaneShapeSettings_CreateShape(const PlaneShapeSettings* settings);
MOSS_API PlaneShape* PlaneShape_Create(const Plane* plane, const PhysicsMaterial* material, float halfExtent);
MOSS_API void PlaneShape_GetPlane(const PlaneShape* shape, Plane* result);
MOSS_API float PlaneShape_GetHalfExtent(const PlaneShape* shape);

/* TriangleShape */
MOSS_API TriangleShapeSettings* TriangleShapeSettings_Create(const Vec3* v1, const Vec3* v2, const Vec3* v3, float convexRadius);
MOSS_API TriangleShape* TriangleShapeSettings_CreateShape(const TriangleShapeSettings* settings);

MOSS_API TriangleShape* TriangleShape_Create(const Vec3* v1, const Vec3* v2, const Vec3* v3, float convexRadius);
MOSS_API float TriangleShape_GetConvexRadius(const TriangleShape* shape);
MOSS_API void TriangleShape_GetVertex1(const TriangleShape* shape, Vec3* result);
MOSS_API void TriangleShape_GetVertex2(const TriangleShape* shape, Vec3* result);
MOSS_API void TriangleShape_GetVertex3(const TriangleShape* shape, Vec3* result);

/* CapsuleShape */
MOSS_API CapsuleShapeSettings* CapsuleShapeSettings_Create(float halfHeightOfCylinder, float radius);
MOSS_API CapsuleShape* CapsuleShapeSettings_CreateShape(const CapsuleShapeSettings* settings);
MOSS_API CapsuleShape* CapsuleShape_Create(float halfHeightOfCylinder, float radius);
MOSS_API float CapsuleShape_GetRadius(const CapsuleShape* shape);
MOSS_API float CapsuleShape_GetHalfHeightOfCylinder(const CapsuleShape* shape);

/* CylinderShape */
MOSS_API CylinderShapeSettings* CylinderShapeSettings_Create(float halfHeight, float radius, float convexRadius);
MOSS_API CylinderShape* CylinderShapeSettings_CreateShape(const CylinderShapeSettings* settings);

MOSS_API CylinderShape* CylinderShape_Create(float halfHeight, float radius);
MOSS_API float CylinderShape_GetRadius(const CylinderShape* shape);
MOSS_API float CylinderShape_GetHalfHeight(const CylinderShape* shape);

/* TaperedCylinderShape */
MOSS_API TaperedCylinderShapeSettings* TaperedCylinderShapeSettings_Create(float halfHeightOfTaperedCylinder, float topRadius, float bottomRadius, float convexRadius/* = cDefaultConvexRadius*/, const PhysicsMaterial* material /* = NULL*/);
MOSS_API TaperedCylinderShape* TaperedCylinderShapeSettings_CreateShape(const TaperedCylinderShapeSettings* settings);
MOSS_API float TaperedCylinderShape_GetTopRadius(const TaperedCylinderShape* shape);
MOSS_API float TaperedCylinderShape_GetBottomRadius(const TaperedCylinderShape* shape);
MOSS_API float TaperedCylinderShape_GetConvexRadius(const TaperedCylinderShape* shape);
MOSS_API float TaperedCylinderShape_GetHalfHeight(const TaperedCylinderShape* shape);

/* ConvexHullShape */
MOSS_API ConvexHullShapeSettings* ConvexHullShapeSettings_Create(const Vec3* points, uint32_t pointsCount, float maxConvexRadius);
MOSS_API ConvexHullShape* ConvexHullShapeSettings_CreateShape(const ConvexHullShapeSettings* settings);
MOSS_API uint32_t ConvexHullShape_GetNumPoints(const ConvexHullShape* shape);
MOSS_API void ConvexHullShape_GetPoint(const ConvexHullShape* shape, uint32_t index, Vec3* result);
MOSS_API uint32_t ConvexHullShape_GetNumFaces(const ConvexHullShape* shape);
MOSS_API uint32_t ConvexHullShape_GetNumVerticesInFace(const ConvexHullShape* shape, uint32_t faceIndex);
MOSS_API uint32_t ConvexHullShape_GetFaceVertices(const ConvexHullShape* shape, uint32_t faceIndex, uint32_t maxVertices, uint32_t* vertices);

/* MeshShape */
MOSS_API MeshShapeSettings* MeshShapeSettings_Create(const Triangle* triangles, uint32_t triangleCount);
MOSS_API MeshShapeSettings* MeshShapeSettings_Create2(const Vec3* vertices, uint32_t verticesCount, const IndexedTriangle* triangles, uint32_t triangleCount);
MOSS_API uint32_t MeshShapeSettings_GetMaxTrianglesPerLeaf(const MeshShapeSettings* settings);
MOSS_API void MeshShapeSettings_SetMaxTrianglesPerLeaf(MeshShapeSettings* settings, uint32_t value);
MOSS_API float MeshShapeSettings_GetActiveEdgeCosThresholdAngle(const MeshShapeSettings* settings);
MOSS_API void MeshShapeSettings_SetActiveEdgeCosThresholdAngle(MeshShapeSettings* settings, float value);
MOSS_API bool MeshShapeSettings_GetPerTriangleUserData(const MeshShapeSettings* settings);
MOSS_API void MeshShapeSettings_SetPerTriangleUserData(MeshShapeSettings* settings, bool value);
MOSS_API Mesh_Shape_BuildQuality MeshShapeSettings_GetBuildQuality(const MeshShapeSettings* settings);
MOSS_API void MeshShapeSettings_SetBuildQuality(MeshShapeSettings* settings, Mesh_Shape_BuildQuality value);

MOSS_API void MeshShapeSettings_Sanitize(MeshShapeSettings* settings);
MOSS_API MeshShape* MeshShapeSettings_CreateShape(const MeshShapeSettings* settings);
MOSS_API uint32_t MeshShape_GetTriangleUserData(const MeshShape* shape, SubShapeID id);

/* HeightFieldShape */
MOSS_API HeightFieldShapeSettings* HeightFieldShapeSettings_Create(const float* samples, const Vec3* offset, const Vec3* scale, uint32_t sampleCount);
MOSS_API HeightFieldShape* HeightFieldShapeSettings_CreateShape(HeightFieldShapeSettings* settings);
MOSS_API void HeightFieldShapeSettings_DetermineMinAndMaxSample(const HeightFieldShapeSettings* settings, float* pOutMinValue, float* pOutMaxValue, float* pOutQuantizationScale);
MOSS_API uint32_t HeightFieldShapeSettings_CalculateBitsPerSampleForError(const HeightFieldShapeSettings* settings, float maxError);

MOSS_API uint32_t HeightFieldShape_GetSampleCount(const HeightFieldShape* shape);
MOSS_API uint32_t HeightFieldShape_GetBlockSize(const HeightFieldShape* shape);
MOSS_API const PhysicsMaterial* HeightFieldShape_GetMaterial(const HeightFieldShape* shape, uint32_t x, uint32_t y);
MOSS_API void HeightFieldShape_GetPosition(const HeightFieldShape* shape, uint32_t x, uint32_t y, Vec3* result);
MOSS_API bool HeightFieldShape_IsNoCollision(const HeightFieldShape* shape, uint32_t x, uint32_t y);
MOSS_API bool HeightFieldShape_ProjectOntoSurface(const HeightFieldShape* shape, const Vec3* localPosition, Vec3* outSurfacePosition, SubShapeID* outSubShapeID);
MOSS_API float HeightFieldShape_GetMinHeightValue(const HeightFieldShape* shape);
MOSS_API float HeightFieldShape_GetMaxHeightValue(const HeightFieldShape* shape);

/* TaperedCapsuleShape */
MOSS_API TaperedCapsuleShapeSettings* TaperedCapsuleShapeSettings_Create(float halfHeightOfTaperedCylinder, float topRadius, float bottomRadius);
MOSS_API TaperedCapsuleShape* TaperedCapsuleShapeSettings_CreateShape(TaperedCapsuleShapeSettings* settings);

MOSS_API float TaperedCapsuleShape_GetTopRadius(const TaperedCapsuleShape* shape);
MOSS_API float TaperedCapsuleShape_GetBottomRadius(const TaperedCapsuleShape* shape);
MOSS_API float TaperedCapsuleShape_GetHalfHeight(const TaperedCapsuleShape* shape);

/* CompoundShape */
MOSS_API void CompoundShapeSettings_AddShape(CompoundShapeSettings* settings, const Vec3* position, const Quat* rotation, const ShapeSettings* shapeSettings, uint32_t userData);
MOSS_API void CompoundShapeSettings_AddShape2(CompoundShapeSettings* settings, const Vec3* position, const Quat* rotation, const Shape* shape, uint32_t userData);
MOSS_API uint32_t CompoundShape_GetNumSubShapes(const CompoundShape* shape);
MOSS_API void CompoundShape_GetSubShape(const CompoundShape* shape, uint32_t index, const Shape** subShape, Vec3* positionCOM, Quat* rotation, uint32_t* userData);
MOSS_API uint32_t CompoundShape_GetSubShapeIndexFromID(const CompoundShape* shape, SubShapeID id, SubShapeID* remainder);

/* StaticCompoundShape */
MOSS_API StaticCompoundShapeSettings* StaticCompoundShapeSettings_Create(void);
MOSS_API StaticCompoundShape* StaticCompoundShape_Create(const StaticCompoundShapeSettings* settings);

/* MutableCompoundShape */
MOSS_API MutableCompoundShapeSettings* MutableCompoundShapeSettings_Create(void);
MOSS_API MutableCompoundShape* MutableCompoundShape_Create(const MutableCompoundShapeSettings* settings);

MOSS_API uint32_t MutableCompoundShape_AddShape(MutableCompoundShape* shape, const Vec3* position, const Quat* rotation, const Shape* child, uint32_t userData /* = 0 */, uint32_t index /* = UINT32_MAX */);
MOSS_API void MutableCompoundShape_RemoveShape(MutableCompoundShape* shape, uint32_t index);
MOSS_API void MutableCompoundShape_ModifyShape(MutableCompoundShape* shape, uint32_t index, const Vec3* position, const Quat* rotation);
MOSS_API void MutableCompoundShape_ModifyShape2(MutableCompoundShape* shape, uint32_t index, const Vec3* position, const Quat* rotation, const Shape* newShape);
MOSS_API void MutableCompoundShape_AdjustCenterOfMass(MutableCompoundShape* shape);

/* DecoratedShape */
MOSS_API const Shape* DecoratedShape_GetInnerShape(const DecoratedShape* shape);

/* RotatedTranslatedShape */
MOSS_API RotatedTranslatedShapeSettings* RotatedTranslatedShapeSettings_Create(const Vec3* position, const Quat* rotation, const ShapeSettings* shapeSettings);
MOSS_API RotatedTranslatedShapeSettings* RotatedTranslatedShapeSettings_Create2(const Vec3* position, const Quat* rotation, const Shape* shape);
MOSS_API RotatedTranslatedShape* RotatedTranslatedShapeSettings_CreateShape(const RotatedTranslatedShapeSettings* settings);
MOSS_API RotatedTranslatedShape* RotatedTranslatedShape_Create(const Vec3* position, const Quat* rotation, const Shape* shape);
MOSS_API void RotatedTranslatedShape_GetPosition(const RotatedTranslatedShape* shape, Vec3* position);
MOSS_API void RotatedTranslatedShape_GetRotation(const RotatedTranslatedShape* shape, Quat* rotation);

/* ScaledShape */
MOSS_API ScaledShapeSettings* ScaledShapeSettings_Create(const ShapeSettings* shapeSettings, const Vec3* scale);
MOSS_API ScaledShapeSettings* ScaledShapeSettings_Create2(const Shape* shape, const Vec3* scale);
MOSS_API ScaledShape* ScaledShapeSettings_CreateShape(const ScaledShapeSettings* settings);
MOSS_API ScaledShape* ScaledShape_Create(const Shape* shape, const Vec3* scale);
MOSS_API void ScaledShape_GetScale(const ScaledShape* shape, Vec3* result);

/* OffsetCenterOfMassShape */
MOSS_API OffsetCenterOfMassShapeSettings* OffsetCenterOfMassShapeSettings_Create(const Vec3* offset, const ShapeSettings* shapeSettings);
MOSS_API OffsetCenterOfMassShapeSettings* OffsetCenterOfMassShapeSettings_Create2(const Vec3* offset, const Shape* shape);
MOSS_API OffsetCenterOfMassShape* OffsetCenterOfMassShapeSettings_CreateShape(const OffsetCenterOfMassShapeSettings* settings);

MOSS_API OffsetCenterOfMassShape* OffsetCenterOfMassShape_Create(const Vec3* offset, const Shape* shape);
MOSS_API void OffsetCenterOfMassShape_GetOffset(const OffsetCenterOfMassShape* shape, Vec3* result);

/* EmptyShape */
MOSS_API EmptyShapeSettings* EmptyShapeSettings_Create(const Vec3* centerOfMass);
MOSS_API EmptyShape* EmptyShapeSettings_CreateShape(const EmptyShapeSettings* settings);

/* BodyCreationSettings */
MOSS_API BodyCreationSettings* BodyCreationSettings_Create(void);
MOSS_API BodyCreationSettings* BodyCreationSettings_Create2(const ShapeSettings* settings,
	const RVec3* position,
	const Quat* rotation,
	MotionType motionType,
	ObjectLayer objectLayer);
MOSS_API BodyCreationSettings* BodyCreationSettings_Create3(const Shape* shape,
	const RVec3* position,
	const Quat* rotation,
	MotionType motionType,
	ObjectLayer objectLayer);
MOSS_API void BodyCreationSettings_Destroy(BodyCreationSettings* settings);

MOSS_API void BodyCreationSettings_GetPosition(BodyCreationSettings* settings, RVec3* result);
MOSS_API void BodyCreationSettings_SetPosition(BodyCreationSettings* settings, const RVec3* value);

MOSS_API void BodyCreationSettings_GetRotation(BodyCreationSettings* settings, Quat* result);
MOSS_API void BodyCreationSettings_SetRotation(BodyCreationSettings* settings, const Quat* value);

MOSS_API void BodyCreationSettings_GetLinearVelocity(BodyCreationSettings* settings, Vec3* velocity);
MOSS_API void BodyCreationSettings_SetLinearVelocity(BodyCreationSettings* settings, const Vec3* velocity);

MOSS_API void BodyCreationSettings_GetAngularVelocity(BodyCreationSettings* settings, Vec3* velocity);
MOSS_API void BodyCreationSettings_SetAngularVelocity(BodyCreationSettings* settings, const Vec3* velocity);

MOSS_API uint64_t BodyCreationSettings_GetUserData(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetUserData(BodyCreationSettings* settings, uint64_t value);

MOSS_API ObjectLayer BodyCreationSettings_GetObjectLayer(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetObjectLayer(BodyCreationSettings* settings, ObjectLayer value);

MOSS_API void BodyCreationSettings_GetCollisionGroup(const BodyCreationSettings* settings, CollisionGroup* result);
MOSS_API void BodyCreationSettings_SetCollisionGroup(BodyCreationSettings* settings, const CollisionGroup* value);

MOSS_API MotionType BodyCreationSettings_GetMotionType(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetMotionType(BodyCreationSettings* settings, MotionType value);

MOSS_API AllowedDOFs BodyCreationSettings_GetAllowedDOFs(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetAllowedDOFs(BodyCreationSettings* settings, AllowedDOFs value);

MOSS_API bool BodyCreationSettings_GetAllowDynamicOrKinematic(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetAllowDynamicOrKinematic(BodyCreationSettings* settings, bool value);

MOSS_API bool BodyCreationSettings_GetIsSensor(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetIsSensor(BodyCreationSettings* settings, bool value);

MOSS_API bool BodyCreationSettings_GetCollideKinematicVsNonDynamic(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetCollideKinematicVsNonDynamic(BodyCreationSettings* settings, bool value);

MOSS_API bool BodyCreationSettings_GetUseManifoldReduction(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetUseManifoldReduction(BodyCreationSettings* settings, bool value);

MOSS_API bool BodyCreationSettings_GetApplyGyroscopicForce(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetApplyGyroscopicForce(BodyCreationSettings* settings, bool value);

MOSS_API MotionQuality BodyCreationSettings_GetMotionQuality(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetMotionQuality(BodyCreationSettings* settings, MotionQuality value);

MOSS_API bool BodyCreationSettings_GetEnhancedInternalEdgeRemoval(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetEnhancedInternalEdgeRemoval(BodyCreationSettings* settings, bool value);

MOSS_API bool BodyCreationSettings_GetAllowSleeping(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetAllowSleeping(BodyCreationSettings* settings, bool value);

MOSS_API float BodyCreationSettings_GetFriction(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetFriction(BodyCreationSettings* settings, float value);

MOSS_API float BodyCreationSettings_GetRestitution(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetRestitution(BodyCreationSettings* settings, float value);

MOSS_API float BodyCreationSettings_GetLinearDamping(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetLinearDamping(BodyCreationSettings* settings, float value);

MOSS_API float BodyCreationSettings_GetAngularDamping(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetAngularDamping(BodyCreationSettings* settings, float value);

MOSS_API float BodyCreationSettings_GetMaxLinearVelocity(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetMaxLinearVelocity(BodyCreationSettings* settings, float value);

MOSS_API float BodyCreationSettings_GetMaxAngularVelocity(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetMaxAngularVelocity(BodyCreationSettings* settings, float value);

MOSS_API float BodyCreationSettings_GetGravityFactor(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetGravityFactor(BodyCreationSettings* settings, float value);

MOSS_API uint32_t BodyCreationSettings_GetNumVelocityStepsOverride(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetNumVelocityStepsOverride(BodyCreationSettings* settings, uint32_t value);

MOSS_API uint32_t BodyCreationSettings_GetNumPositionStepsOverride(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetNumPositionStepsOverride(BodyCreationSettings* settings, uint32_t value);

MOSS_API OverrideMassProperties BodyCreationSettings_GetOverrideMassProperties(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetOverrideMassProperties(BodyCreationSettings* settings, OverrideMassProperties value);

MOSS_API float BodyCreationSettings_GetInertiaMultiplier(const BodyCreationSettings* settings);
MOSS_API void BodyCreationSettings_SetInertiaMultiplier(BodyCreationSettings* settings, float value);

MOSS_API void BodyCreationSettings_GetMassPropertiesOverride(const BodyCreationSettings* settings, MassProperties* result);
MOSS_API void BodyCreationSettings_SetMassPropertiesOverride(BodyCreationSettings* settings, const MassProperties* massProperties);

/* SoftBodyCreationSettings */
MOSS_API SoftBodyCreationSettings* SoftBodyCreationSettings_Create(void);
MOSS_API void SoftBodyCreationSettings_Destroy(SoftBodyCreationSettings* settings);

/* Constraint */
MOSS_API void Constraint_Destroy(Constraint* constraint);
MOSS_API ConstraintType Constraint_GetType(const Constraint* constraint);
MOSS_API ConstraintSubType Constraint_GetSubType(const Constraint* constraint);
MOSS_API uint32_t Constraint_GetConstraintPriority(const Constraint* constraint);
MOSS_API void Constraint_SetConstraintPriority(Constraint* constraint, uint32_t priority);
MOSS_API uint32_t Constraint_GetNumVelocityStepsOverride(const Constraint* constraint);
MOSS_API void Constraint_SetNumVelocityStepsOverride(Constraint* constraint, uint32_t value);
MOSS_API uint32_t Constraint_GetNumPositionStepsOverride(const Constraint* constraint);
MOSS_API void Constraint_SetNumPositionStepsOverride(Constraint* constraint, uint32_t value);
MOSS_API bool Constraint_GetEnabled(const Constraint* constraint);
MOSS_API void Constraint_SetEnabled(Constraint* constraint, bool enabled);
MOSS_API uint64_t Constraint_GetUserData(const Constraint* constraint);
MOSS_API void Constraint_SetUserData(Constraint* constraint, uint64_t userData);
MOSS_API void Constraint_NotifyShapeChanged(Constraint* constraint, BodyID bodyID, Vec3* deltaCOM);
MOSS_API void Constraint_ResetWarmStart(Constraint* constraint);
MOSS_API bool Constraint_IsActive(const Constraint* constraint);
MOSS_API void Constraint_SetupVelocityConstraint(Constraint* constraint, float deltaTime);
MOSS_API void Constraint_WarmStartVelocityConstraint(Constraint* constraint, float warmStartImpulseRatio);
MOSS_API bool Constraint_SolveVelocityConstraint(Constraint* constraint, float deltaTime);
MOSS_API bool Constraint_SolvePositionConstraint(Constraint* constraint, float deltaTime, float baumgarte);

/* TwoBodyConstraint */
MOSS_API Body* TwoBodyConstraint_GetBody1(const TwoBodyConstraint* constraint);
MOSS_API Body* TwoBodyConstraint_GetBody2(const TwoBodyConstraint* constraint);
MOSS_API void TwoBodyConstraint_GetConstraintToBody1Matrix(const TwoBodyConstraint* constraint, Matrix4x4* result);
MOSS_API void TwoBodyConstraint_GetConstraintToBody2Matrix(const TwoBodyConstraint* constraint, Matrix4x4* result);

/* FixedConstraint */
MOSS_API void FixedConstraintSettings_Init(FixedConstraintSettings* settings);
MOSS_API FixedConstraint* FixedConstraint_Create(const FixedConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void FixedConstraint_GetSettings(const FixedConstraint* constraint, FixedConstraintSettings* settings);
MOSS_API void FixedConstraint_GetTotalLambdaPosition(const FixedConstraint* constraint, Vec3* result);
MOSS_API void FixedConstraint_GetTotalLambdaRotation(const FixedConstraint* constraint, Vec3* result);

/* DistanceConstraint */
MOSS_API void DistanceConstraintSettings_Init(DistanceConstraintSettings* settings);
MOSS_API DistanceConstraint* DistanceConstraint_Create(const DistanceConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void DistanceConstraint_GetSettings(const DistanceConstraint* constraint, DistanceConstraintSettings* settings);
MOSS_API void DistanceConstraint_SetDistance(DistanceConstraint* constraint, float minDistance, float maxDistance);
MOSS_API float DistanceConstraint_GetMinDistance(DistanceConstraint* constraint);
MOSS_API float DistanceConstraint_GetMaxDistance(DistanceConstraint* constraint);
MOSS_API void DistanceConstraint_GetLimitsSpringSettings(DistanceConstraint* constraint, SpringSettings* result);
MOSS_API void DistanceConstraint_SetLimitsSpringSettings(DistanceConstraint* constraint, SpringSettings* settings);
MOSS_API float DistanceConstraint_GetTotalLambdaPosition(const DistanceConstraint* constraint);

/* PointConstraint */
MOSS_API void PointConstraintSettings_Init(PointConstraintSettings* settings);
MOSS_API PointConstraint* PointConstraint_Create(const PointConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void PointConstraint_GetSettings(const PointConstraint* constraint, PointConstraintSettings* settings);
MOSS_API void PointConstraint_SetPoint1(PointConstraint* constraint, ConstraintSpace space, RVec3* value);
MOSS_API void PointConstraint_SetPoint2(PointConstraint* constraint, ConstraintSpace space, RVec3* value);
MOSS_API void PointConstraint_GetLocalSpacePoint1(const PointConstraint* constraint, Vec3* result);
MOSS_API void PointConstraint_GetLocalSpacePoint2(const PointConstraint* constraint, Vec3* result);
MOSS_API void PointConstraint_GetTotalLambdaPosition(const PointConstraint* constraint, Vec3* result);

/* HingeConstraint */
MOSS_API void HingeConstraintSettings_Init(HingeConstraintSettings* settings);
MOSS_API HingeConstraint* HingeConstraint_Create(const HingeConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void HingeConstraint_GetSettings(HingeConstraint* constraint, HingeConstraintSettings* settings);
MOSS_API void HingeConstraint_GetLocalSpacePoint1(const HingeConstraint* constraint, Vec3* result);
MOSS_API void HingeConstraint_GetLocalSpacePoint2(const HingeConstraint* constraint, Vec3* result);
MOSS_API void HingeConstraint_GetLocalSpaceHingeAxis1(const HingeConstraint* constraint, Vec3* result);
MOSS_API void HingeConstraint_GetLocalSpaceHingeAxis2(const HingeConstraint* constraint, Vec3* result);
MOSS_API void HingeConstraint_GetLocalSpaceNormalAxis1(const HingeConstraint* constraint, Vec3* result);
MOSS_API void HingeConstraint_GetLocalSpaceNormalAxis2(const HingeConstraint* constraint, Vec3* result);
MOSS_API float HingeConstraint_GetCurrentAngle(HingeConstraint* constraint);
MOSS_API void HingeConstraint_SetMaxFrictionTorque(HingeConstraint* constraint, float frictionTorque);
MOSS_API float HingeConstraint_GetMaxFrictionTorque(HingeConstraint* constraint);
MOSS_API void HingeConstraint_SetMotorSettings(HingeConstraint* constraint, MotorSettings* settings);
MOSS_API void HingeConstraint_GetMotorSettings(HingeConstraint* constraint, MotorSettings* result);
MOSS_API void HingeConstraint_SetMotorState(HingeConstraint* constraint, MotorState state);
MOSS_API MotorState HingeConstraint_GetMotorState(HingeConstraint* constraint);
MOSS_API void HingeConstraint_SetTargetAngularVelocity(HingeConstraint* constraint, float angularVelocity);
MOSS_API float HingeConstraint_GetTargetAngularVelocity(HingeConstraint* constraint);
MOSS_API void HingeConstraint_SetTargetAngle(HingeConstraint* constraint, float angle);
MOSS_API float HingeConstraint_GetTargetAngle(HingeConstraint* constraint);
MOSS_API void HingeConstraint_SetLimits(HingeConstraint* constraint, float inLimitsMin, float inLimitsMax);
MOSS_API float HingeConstraint_GetLimitsMin(HingeConstraint* constraint);
MOSS_API float HingeConstraint_GetLimitsMax(HingeConstraint* constraint);
MOSS_API bool HingeConstraint_HasLimits(HingeConstraint* constraint);
MOSS_API void HingeConstraint_GetLimitsSpringSettings(HingeConstraint* constraint, SpringSettings* result);
MOSS_API void HingeConstraint_SetLimitsSpringSettings(HingeConstraint* constraint, SpringSettings* settings);
MOSS_API void HingeConstraint_GetTotalLambdaPosition(const HingeConstraint* constraint, Vec3* result);
MOSS_API void HingeConstraint_GetTotalLambdaRotation(const HingeConstraint* constraint, float rotation[2]);
MOSS_API float HingeConstraint_GetTotalLambdaRotationLimits(const HingeConstraint* constraint);
MOSS_API float HingeConstraint_GetTotalLambdaMotor(const HingeConstraint* constraint);

/* SliderConstraint */
MOSS_API void SliderConstraintSettings_Init(SliderConstraintSettings* settings);
MOSS_API void SliderConstraintSettings_SetSliderAxis(SliderConstraintSettings* settings, const Vec3* axis);

MOSS_API SliderConstraint* SliderConstraint_Create(const SliderConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void SliderConstraint_GetSettings(SliderConstraint* constraint, SliderConstraintSettings* settings);
MOSS_API float SliderConstraint_GetCurrentPosition(SliderConstraint* constraint);
MOSS_API void SliderConstraint_SetMaxFrictionForce(SliderConstraint* constraint, float frictionForce);
MOSS_API float SliderConstraint_GetMaxFrictionForce(SliderConstraint* constraint);
MOSS_API void SliderConstraint_SetMotorSettings(SliderConstraint* constraint, MotorSettings* settings);
MOSS_API void SliderConstraint_GetMotorSettings(const SliderConstraint* constraint, MotorSettings* result);
MOSS_API void SliderConstraint_SetMotorState(SliderConstraint* constraint, MotorState state);
MOSS_API MotorState SliderConstraint_GetMotorState(SliderConstraint* constraint);
MOSS_API void SliderConstraint_SetTargetVelocity(SliderConstraint* constraint, float velocity);
MOSS_API float SliderConstraint_GetTargetVelocity(SliderConstraint* constraint);
MOSS_API void SliderConstraint_SetTargetPosition(SliderConstraint* constraint, float position);
MOSS_API float SliderConstraint_GetTargetPosition(SliderConstraint* constraint);
MOSS_API void SliderConstraint_SetLimits(SliderConstraint* constraint, float inLimitsMin, float inLimitsMax);
MOSS_API float SliderConstraint_GetLimitsMin(SliderConstraint* constraint);
MOSS_API float SliderConstraint_GetLimitsMax(SliderConstraint* constraint);
MOSS_API bool SliderConstraint_HasLimits(SliderConstraint* constraint);
MOSS_API void SliderConstraint_GetLimitsSpringSettings(SliderConstraint* constraint, SpringSettings* result);
MOSS_API void SliderConstraint_SetLimitsSpringSettings(SliderConstraint* constraint, SpringSettings* settings);
MOSS_API void SliderConstraint_GetTotalLambdaPosition(const SliderConstraint* constraint, float position[2]);
MOSS_API float SliderConstraint_GetTotalLambdaPositionLimits(const SliderConstraint* constraint);
MOSS_API void SliderConstraint_GetTotalLambdaRotation(const SliderConstraint* constraint, Vec3* result);
MOSS_API float SliderConstraint_GetTotalLambdaMotor(const SliderConstraint* constraint);

/* ConeConstraint */
MOSS_API void ConeConstraintSettings_Init(ConeConstraintSettings* settings);
MOSS_API ConeConstraint* ConeConstraint_Create(const ConeConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void ConeConstraint_GetSettings(ConeConstraint* constraint, ConeConstraintSettings* settings);
MOSS_API void ConeConstraint_SetHalfConeAngle(ConeConstraint* constraint, float halfConeAngle);
MOSS_API float ConeConstraint_GetCosHalfConeAngle(const ConeConstraint* constraint);
MOSS_API void ConeConstraint_GetTotalLambdaPosition(const ConeConstraint* constraint, Vec3* result);
MOSS_API float ConeConstraint_GetTotalLambdaRotation(const ConeConstraint* constraint);

/* SwingTwistConstraint */
MOSS_API void SwingTwistConstraintSettings_Init(SwingTwistConstraintSettings* settings);
MOSS_API SwingTwistConstraint* SwingTwistConstraint_Create(const SwingTwistConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void SwingTwistConstraint_GetSettings(SwingTwistConstraint* constraint, SwingTwistConstraintSettings* settings);
MOSS_API float SwingTwistConstraint_GetNormalHalfConeAngle(SwingTwistConstraint* constraint);
MOSS_API void SwingTwistConstraint_GetTotalLambdaPosition(const SwingTwistConstraint* constraint, Vec3* result);
MOSS_API float SwingTwistConstraint_GetTotalLambdaTwist(const SwingTwistConstraint* constraint);
MOSS_API float SwingTwistConstraint_GetTotalLambdaSwingY(const SwingTwistConstraint* constraint);
MOSS_API float SwingTwistConstraint_GetTotalLambdaSwingZ(const SwingTwistConstraint* constraint);
MOSS_API void SwingTwistConstraint_GetTotalLambdaMotor(const SwingTwistConstraint* constraint, Vec3* result);

/* SixDOFConstraint */
MOSS_API void SixDOFConstraintSettings_Init(SixDOFConstraintSettings* settings);
MOSS_API void SixDOFConstraintSettings_MakeFreeAxis(SixDOFConstraintSettings* settings, SixDOFConstraintAxis axis);
MOSS_API bool SixDOFConstraintSettings_IsFreeAxis(const SixDOFConstraintSettings* settings, SixDOFConstraintAxis axis);
MOSS_API void SixDOFConstraintSettings_MakeFixedAxis(SixDOFConstraintSettings* settings, SixDOFConstraintAxis axis);
MOSS_API bool SixDOFConstraintSettings_IsFixedAxis(const SixDOFConstraintSettings* settings, SixDOFConstraintAxis axis);
MOSS_API void SixDOFConstraintSettings_SetLimitedAxis(SixDOFConstraintSettings* settings, SixDOFConstraintAxis axis, float min, float max);

MOSS_API SixDOFConstraint* SixDOFConstraint_Create(const SixDOFConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void SixDOFConstraint_GetSettings(SixDOFConstraint* constraint, SixDOFConstraintSettings* settings);
MOSS_API float SixDOFConstraint_GetLimitsMin(SixDOFConstraint* constraint, SixDOFConstraintAxis axis);
MOSS_API float SixDOFConstraint_GetLimitsMax(SixDOFConstraint* constraint, SixDOFConstraintAxis axis);
MOSS_API void SixDOFConstraint_GetTotalLambdaPosition(const SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_GetTotalLambdaRotation(const SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_GetTotalLambdaMotorTranslation(const SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_GetTotalLambdaMotorRotation(const SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_GetTranslationLimitsMin(const SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_GetTranslationLimitsMax(const SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_GetRotationLimitsMin(const SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_GetRotationLimitsMax(const SixDOFConstraint* constraint, Vec3* result);
MOSS_API bool SixDOFConstraint_IsFixedAxis(const SixDOFConstraint* constraint, SixDOFConstraintAxis axis);
MOSS_API bool SixDOFConstraint_IsFreeAxis(const SixDOFConstraint* constraint, SixDOFConstraintAxis axis);
MOSS_API void SixDOFConstraint_GetLimitsSpringSettings(SixDOFConstraint* constraint, SpringSettings* result, SixDOFConstraintAxis axis);
MOSS_API void SixDOFConstraint_SetLimitsSpringSettings(SixDOFConstraint* constraint, SpringSettings* settings, SixDOFConstraintAxis axis);
MOSS_API void SixDOFConstraint_SetMaxFriction(SixDOFConstraint* constraint, SixDOFConstraintAxis axis, float inFriction);
MOSS_API float SixDOFConstraint_GetMaxFriction(SixDOFConstraint* constraint, SixDOFConstraintAxis axis);
MOSS_API void SixDOFConstraint_GetRotationInConstraintSpace(SixDOFConstraint* constraint, Quat* result);
MOSS_API void SixDOFConstraint_GetMotorSettings(SixDOFConstraint* constraint, SixDOFConstraintAxis axis, MotorSettings* settings);
MOSS_API void SixDOFConstraint_SetMotorState(SixDOFConstraint* constraint, SixDOFConstraintAxis axis, MotorState state);
MOSS_API MotorState SixDOFConstraint_GetMotorState(SixDOFConstraint* constraint, SixDOFConstraintAxis axis);
MOSS_API void SixDOFConstraint_SetTargetVelocityCS(SixDOFConstraint* constraint, Vec3* inVelocity);
MOSS_API void SixDOFConstraint_GetTargetVelocityCS(SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_SetTargetAngularVelocityCS(SixDOFConstraint* constraint, Vec3* inAngularVelocity);
MOSS_API void SixDOFConstraint_GetTargetAngularVelocityCS(SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_SetTargetPositionCS(SixDOFConstraint* constraint, Vec3* inPosition);
MOSS_API void SixDOFConstraint_GetTargetPositionCS(SixDOFConstraint* constraint, Vec3* result);
MOSS_API void SixDOFConstraint_SetTargetOrientationCS(SixDOFConstraint* constraint, Quat* inOrientation);
MOSS_API void SixDOFConstraint_GetTargetOrientationCS(SixDOFConstraint* constraint, Quat* result);
MOSS_API void SixDOFConstraint_SetTargetOrientationBS(SixDOFConstraint* constraint, Quat* inOrientation);

/* GearConstraint */
MOSS_API void GearConstraintSettings_Init(GearConstraintSettings* settings);
MOSS_API GearConstraint* GearConstraint_Create(const GearConstraintSettings* settings, Body* body1, Body* body2);
MOSS_API void GearConstraint_GetSettings(GearConstraint* constraint, GearConstraintSettings* settings);
MOSS_API void GearConstraint_SetConstraints(GearConstraint* constraint, const Constraint* gear1, const Constraint* gear2);
MOSS_API float GearConstraint_GetTotalLambda(const GearConstraint* constraint);

/* BodyInterface */
MOSS_API void BodyInterface_DestroyBody(BodyInterface* bodyInterface, BodyID bodyID);
MOSS_API BodyID BodyInterface_CreateAndAddBody(BodyInterface* bodyInterface, const BodyCreationSettings* settings, Activation activationMode);
MOSS_API Body* BodyInterface_CreateBody(BodyInterface* bodyInterface, const BodyCreationSettings* settings);
MOSS_API Body* BodyInterface_CreateBodyWithID(BodyInterface* bodyInterface, BodyID bodyID, const BodyCreationSettings* settings);
MOSS_API Body* BodyInterface_CreateBodyWithoutID(BodyInterface* bodyInterface, const BodyCreationSettings* settings);
MOSS_API void BodyInterface_DestroyBodyWithoutID(BodyInterface* bodyInterface, Body* body);
MOSS_API bool BodyInterface_AssignBodyID(BodyInterface* bodyInterface, Body* body);
MOSS_API bool BodyInterface_AssignBodyID2(BodyInterface* bodyInterface, Body* body, BodyID bodyID);
MOSS_API Body* BodyInterface_UnassignBodyID(BodyInterface* bodyInterface, BodyID bodyID);

MOSS_API Body* BodyInterface_CreateSoftBody(BodyInterface* bodyInterface, const SoftBodyCreationSettings* settings);
MOSS_API Body* BodyInterface_CreateSoftBodyWithID(BodyInterface* bodyInterface, BodyID bodyID, const SoftBodyCreationSettings* settings);
MOSS_API Body* BodyInterface_CreateSoftBodyWithoutID(BodyInterface* bodyInterface, const SoftBodyCreationSettings* settings);
MOSS_API BodyID BodyInterface_CreateAndAddSoftBody(BodyInterface* bodyInterface, const SoftBodyCreationSettings* settings, Activation activationMode);

MOSS_API void BodyInterface_AddBody(BodyInterface* bodyInterface, BodyID bodyID, Activation activationMode);
MOSS_API void BodyInterface_RemoveBody(BodyInterface* bodyInterface, BodyID bodyID);
MOSS_API void BodyInterface_RemoveAndDestroyBody(BodyInterface* bodyInterface, BodyID bodyID);
MOSS_API bool BodyInterface_IsActive(BodyInterface* bodyInterface, BodyID bodyID);
MOSS_API bool BodyInterface_IsAdded(BodyInterface* bodyInterface, BodyID bodyID);
MOSS_API BodyType BodyInterface_GetBodyType(BodyInterface* bodyInterface, BodyID bodyID);

MOSS_API void BodyInterface_SetLinearVelocity(BodyInterface* bodyInterface, BodyID bodyID, const Vec3* velocity);
MOSS_API void BodyInterface_GetLinearVelocity(BodyInterface* bodyInterface, BodyID bodyID, Vec3* velocity);
MOSS_API void BodyInterface_GetCenterOfMassPosition(BodyInterface* bodyInterface, BodyID bodyID, RVec3* position);

MOSS_API MotionType BodyInterface_GetMotionType(BodyInterface* bodyInterface, BodyID bodyID);
MOSS_API void BodyInterface_SetMotionType(BodyInterface* bodyInterface, BodyID bodyID, MotionType motionType, Activation activationMode);

MOSS_API float BodyInterface_GetRestitution(const BodyInterface* bodyInterface, BodyID bodyID);
MOSS_API void BodyInterface_SetRestitution(BodyInterface* bodyInterface, BodyID bodyID, float restitution);

MOSS_API float BodyInterface_GetFriction(const BodyInterface* bodyInterface, BodyID bodyID);
MOSS_API void BodyInterface_SetFriction(BodyInterface* bodyInterface, BodyID bodyID, float friction);

MOSS_API void BodyInterface_SetPosition(BodyInterface* bodyInterface, BodyID bodyId, RVec3* position, Activation activationMode);
MOSS_API void BodyInterface_GetPosition(BodyInterface* bodyInterface, BodyID bodyId, RVec3* result);

MOSS_API void BodyInterface_SetRotation(BodyInterface* bodyInterface, BodyID bodyId, Quat* rotation, Activation activationMode);
MOSS_API void BodyInterface_GetRotation(BodyInterface* bodyInterface, BodyID bodyId, Quat* result);

MOSS_API void BodyInterface_SetPositionAndRotation(BodyInterface* bodyInterface, BodyID bodyId, const RVec3* position, const Quat* rotation, Activation activationMode);
MOSS_API void BodyInterface_SetPositionAndRotationWhenChanged(BodyInterface* bodyInterface, BodyID bodyId, const RVec3* position, const Quat* rotation, Activation activationMode);
MOSS_API void BodyInterface_GetPositionAndRotation(BodyInterface* bodyInterface, BodyID bodyId, RVec3* position, Quat* rotation);
MOSS_API void BodyInterface_SetPositionRotationAndVelocity(BodyInterface* bodyInterface, BodyID bodyId, RVec3* position, Quat* rotation, Vec3* linearVelocity, Vec3* angularVelocity);

MOSS_API void BodyInterface_GetCollisionGroup(BodyInterface* bodyInterface, BodyID bodyId, CollisionGroup* result);
MOSS_API void BodyInterface_SetCollisionGroup(BodyInterface* bodyInterface, BodyID bodyId, const CollisionGroup* group);

MOSS_API const Shape* BodyInterface_GetShape(BodyInterface* bodyInterface, BodyID bodyId);
MOSS_API void BodyInterface_SetShape(BodyInterface* bodyInterface, BodyID bodyId, const Shape* shape, bool updateMassProperties, Activation activationMode);
MOSS_API void BodyInterface_NotifyShapeChanged(BodyInterface* bodyInterface, BodyID bodyId, Vec3* previousCenterOfMass, bool updateMassProperties, Activation activationMode);

MOSS_API void BodyInterface_ActivateBody(BodyInterface* bodyInterface, BodyID bodyId);
MOSS_API void BodyInterface_DeactivateBody(BodyInterface* bodyInterface, BodyID bodyId);

MOSS_API ObjectLayer BodyInterface_GetObjectLayer(BodyInterface* bodyInterface, BodyID bodyId);
MOSS_API void BodyInterface_SetObjectLayer(BodyInterface* bodyInterface, BodyID bodyId, ObjectLayer layer);

MOSS_API void BodyInterface_GetWorldTransform(BodyInterface* bodyInterface, BodyID bodyId, RMatrix4x4* result);
MOSS_API void BodyInterface_GetCenterOfMassTransform(BodyInterface* bodyInterface, BodyID bodyId, RMatrix4x4* result);

MOSS_API void BodyInterface_MoveKinematic(BodyInterface* bodyInterface, BodyID bodyId, RVec3* targetPosition, Quat* targetRotation, float deltaTime);
MOSS_API bool BodyInterface_ApplyBuoyancyImpulse(BodyInterface* bodyInterface, BodyID bodyId, const RVec3* surfacePosition, const Vec3* surfaceNormal, float buoyancy, float linearDrag, float angularDrag, const Vec3* fluidVelocity, const Vec3* gravity, float deltaTime);

MOSS_API void BodyInterface_SetLinearAndAngularVelocity(BodyInterface* bodyInterface, BodyID bodyId, Vec3* linearVelocity, Vec3* angularVelocity);
MOSS_API void BodyInterface_GetLinearAndAngularVelocity(BodyInterface* bodyInterface, BodyID bodyId, Vec3* linearVelocity, Vec3* angularVelocity);

MOSS_API void BodyInterface_AddLinearVelocity(BodyInterface* bodyInterface, BodyID bodyId, Vec3* linearVelocity);
MOSS_API void BodyInterface_AddLinearAndAngularVelocity(BodyInterface* bodyInterface, BodyID bodyId, Vec3* linearVelocity, Vec3* angularVelocity);

MOSS_API void BodyInterface_SetAngularVelocity(BodyInterface* bodyInterface, BodyID bodyId, Vec3* angularVelocity);
MOSS_API void BodyInterface_GetAngularVelocity(BodyInterface* bodyInterface, BodyID bodyId, Vec3* angularVelocity);

MOSS_API void BodyInterface_GetPointVelocity(BodyInterface* bodyInterface, BodyID bodyId, RVec3* point, Vec3* velocity);

MOSS_API void BodyInterface_AddForce(BodyInterface* bodyInterface, BodyID bodyId, Vec3* force);
MOSS_API void BodyInterface_AddForce2(BodyInterface* bodyInterface, BodyID bodyId, Vec3* force, RVec3* point);
MOSS_API void BodyInterface_AddTorque(BodyInterface* bodyInterface, BodyID bodyId, Vec3* torque);
MOSS_API void BodyInterface_AddForceAndTorque(BodyInterface* bodyInterface, BodyID bodyId, Vec3* force, Vec3* torque);

MOSS_API void BodyInterface_AddImpulse(BodyInterface* bodyInterface, BodyID bodyId, Vec3* impulse);
MOSS_API void BodyInterface_AddImpulse2(BodyInterface* bodyInterface, BodyID bodyId, Vec3* impulse, RVec3* point);
MOSS_API void BodyInterface_AddAngularImpulse(BodyInterface* bodyInterface, BodyID bodyId, Vec3* angularImpulse);

MOSS_API void BodyInterface_SetMotionQuality(BodyInterface* bodyInterface, BodyID bodyId, MotionQuality quality);
MOSS_API MotionQuality BodyInterface_GetMotionQuality(BodyInterface* bodyInterface, BodyID bodyId);

MOSS_API void BodyInterface_GetInverseInertia(BodyInterface* bodyInterface, BodyID bodyId, Matrix4x4* result);

MOSS_API void BodyInterface_SetGravityFactor(BodyInterface* bodyInterface, BodyID bodyId, float value);
MOSS_API float BodyInterface_GetGravityFactor(BodyInterface* bodyInterface, BodyID bodyId);

MOSS_API void BodyInterface_SetUseManifoldReduction(BodyInterface* bodyInterface, BodyID bodyId, bool value);
MOSS_API bool BodyInterface_GetUseManifoldReduction(BodyInterface* bodyInterface, BodyID bodyId);

MOSS_API void BodyInterface_SetUserData(BodyInterface* bodyInterface, BodyID bodyId, uint64_t inUserData);
MOSS_API uint64_t BodyInterface_GetUserData(BodyInterface* bodyInterface, BodyID bodyId);

MOSS_API void BodyInterface_SetIsSensor(BodyInterface* bodyInterface, BodyID bodyId, bool value);
MOSS_API bool BodyInterface_IsSensor(BodyInterface* bodyInterface, BodyID bodyId);

MOSS_API const PhysicsMaterial* BodyInterface_GetMaterial(BodyInterface* bodyInterface, BodyID bodyId, SubShapeID subShapeID);

MOSS_API void BodyInterface_InvalidateContactCache(BodyInterface* bodyInterface, BodyID bodyId);

//--------------------------------------------------------------------------------------------------
// BodyLockInterface
//--------------------------------------------------------------------------------------------------
MOSS_API void BodyLockInterface_LockRead(const BodyLockInterface* lockInterface, BodyID bodyID, BodyLockRead* outLock);
MOSS_API void BodyLockInterface_UnlockRead(const BodyLockInterface* lockInterface, BodyLockRead* ioLock);

MOSS_API void BodyLockInterface_LockWrite(const BodyLockInterface* lockInterface, BodyID bodyID, BodyLockWrite* outLock);
MOSS_API void BodyLockInterface_UnlockWrite(const BodyLockInterface* lockInterface, BodyLockWrite* ioLock);

MOSS_API BodyLockMultiRead* BodyLockInterface_LockMultiRead(const BodyLockInterface* lockInterface, const BodyID* bodyIDs, uint32_t count);
MOSS_API void BodyLockMultiRead_Destroy(BodyLockMultiRead* ioLock);
MOSS_API const Body* BodyLockMultiRead_GetBody(BodyLockMultiRead* ioLock, uint32_t bodyIndex);

MOSS_API BodyLockMultiWrite* BodyLockInterface_LockMultiWrite(const BodyLockInterface* lockInterface, const BodyID* bodyIDs, uint32_t count);
MOSS_API void BodyLockMultiWrite_Destroy(BodyLockMultiWrite* ioLock);
MOSS_API Body* BodyLockMultiWrite_GetBody(BodyLockMultiWrite* ioLock, uint32_t bodyIndex);

//--------------------------------------------------------------------------------------------------
// MotionProperties
//--------------------------------------------------------------------------------------------------
MOSS_API AllowedDOFs MotionProperties_GetAllowedDOFs(const MotionProperties* properties);
MOSS_API void MotionProperties_SetLinearDamping(MotionProperties* properties, float damping);
MOSS_API float MotionProperties_GetLinearDamping(const MotionProperties* properties);
MOSS_API void MotionProperties_SetAngularDamping(MotionProperties* properties, float damping);
MOSS_API float MotionProperties_GetAngularDamping(const MotionProperties* properties);
MOSS_API void MotionProperties_SetMassProperties(MotionProperties* properties, AllowedDOFs allowedDOFs, const MassProperties* massProperties);
MOSS_API float MotionProperties_GetInverseMassUnchecked(MotionProperties* properties);
MOSS_API void MotionProperties_SetInverseMass(MotionProperties* properties, float inverseMass);
MOSS_API void MotionProperties_GetInverseInertiaDiagonal(MotionProperties* properties, Vec3* result);
MOSS_API void MotionProperties_GetInertiaRotation(MotionProperties* properties, Quat* result);
MOSS_API void MotionProperties_SetInverseInertia(MotionProperties* properties, Vec3* diagonal, Quat* rot);
MOSS_API void MotionProperties_ScaleToMass(MotionProperties* properties, float mass);

//--------------------------------------------------------------------------------------------------
// RayCast
//--------------------------------------------------------------------------------------------------
MOSS_API void RayCast_GetPointOnRay(const Vec3* origin, const Vec3* direction, float fraction, Vec3* result);
MOSS_API void RRayCast_GetPointOnRay(const RVec3* origin, const Vec3* direction, float fraction, RVec3* result);

//--------------------------------------------------------------------------------------------------
// MassProperties
//--------------------------------------------------------------------------------------------------
MOSS_API void MassProperties_DecomposePrincipalMomentsOfInertia(MassProperties* properties, Matrix4x4* rotation, Vec3* diagonal);
MOSS_API void MassProperties_ScaleToMass(MassProperties* properties, float mass);
MOSS_API void MassProperties_GetEquivalentSolidBoxSize(float mass, const Vec3* inertiaDiagonal, Vec3* result);

//--------------------------------------------------------------------------------------------------
// CollideShapeSettings
//--------------------------------------------------------------------------------------------------
MOSS_API void CollideShapeSettings_Init(CollideShapeSettings* settings);

//--------------------------------------------------------------------------------------------------
// ShapeCastSettings
//--------------------------------------------------------------------------------------------------
MOSS_API void ShapeCastSettings_Init(ShapeCastSettings* settings);

//--------------------------------------------------------------------------------------------------
// BroadPhaseQuery
//--------------------------------------------------------------------------------------------------
MOSS_API bool BroadPhaseQuery_CastRay(const BroadPhaseQuery* query,
	const Vec3* origin, const Vec3* direction,
	RayCastBodyCollectorCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter);

MOSS_API bool BroadPhaseQuery_CastRay2(const BroadPhaseQuery* query,
	const Vec3* origin, const Vec3* direction,
	CollisionCollectorType collectorType,
	RayCastBodyResultCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter);

MOSS_API bool BroadPhaseQuery_CollideAABB3(const BroadPhaseQuery* query,
	const AABB3* box, CollideShapeBodyCollectorCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter);

MOSS_API bool BroadPhaseQuery_CollideSphere(const BroadPhaseQuery* query,
	const Vec3* center, float radius, CollideShapeBodyCollectorCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter);

MOSS_API bool BroadPhaseQuery_CollidePoint(const BroadPhaseQuery* query,
	const Vec3* point, CollideShapeBodyCollectorCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter);

//--------------------------------------------------------------------------------------------------
// NarrowPhaseQuery
//--------------------------------------------------------------------------------------------------
MOSS_API bool NarrowPhaseQuery_CastRay(const NarrowPhaseQuery* query,
	const RVec3* origin, const Vec3* direction,
	RayCastResult* hit,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter);

MOSS_API bool NarrowPhaseQuery_CastRay2(const NarrowPhaseQuery* query,
	const RVec3* origin, const Vec3* direction,
	const RayCastSettings* rayCastSettings,
	CastRayCollectorCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter,
	const ShapeFilter* shapeFilter);

MOSS_API bool NarrowPhaseQuery_CastRay3(const NarrowPhaseQuery* query,
	const RVec3* origin, const Vec3* direction,
	const RayCastSettings* rayCastSettings,
	CollisionCollectorType collectorType,
	CastRayResultCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter,
	const ShapeFilter* shapeFilter);

MOSS_API bool NarrowPhaseQuery_CollidePoint(const NarrowPhaseQuery* query,
	const RVec3* point,
	CollidePointCollectorCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter,
	const ShapeFilter* shapeFilter);

MOSS_API bool NarrowPhaseQuery_CollidePoint2(const NarrowPhaseQuery* query,
	const RVec3* point,
	CollisionCollectorType collectorType,
	CollidePointResultCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter,
	const ShapeFilter* shapeFilter);

MOSS_API bool NarrowPhaseQuery_CollideShape(const NarrowPhaseQuery* query,
	const Shape* shape, const Vec3* scale, const RMatrix4x4* centerOfMassTransform,
	const CollideShapeSettings* settings,
	RVec3* baseOffset,
	CollideShapeCollectorCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter,
	const ShapeFilter* shapeFilter);

MOSS_API bool NarrowPhaseQuery_CollideShape2(const NarrowPhaseQuery* query,
	const Shape* shape, const Vec3* scale, const RMatrix4x4* centerOfMassTransform,
	const CollideShapeSettings* settings,
	RVec3* baseOffset,
	CollisionCollectorType collectorType,
	CollideShapeResultCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter,
	const ShapeFilter* shapeFilter);

MOSS_API bool NarrowPhaseQuery_CastShape(const NarrowPhaseQuery* query,
	const Shape* shape,
	const RMatrix4x4* worldTransform, const Vec3* direction,
	const ShapeCastSettings* settings,
	RVec3* baseOffset,
	CastShapeCollectorCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter,
	const ShapeFilter* shapeFilter);

MOSS_API bool NarrowPhaseQuery_CastShape2(const NarrowPhaseQuery* query,
	const Shape* shape,
	const RMatrix4x4* worldTransform, const Vec3* direction,
	const ShapeCastSettings* settings,
	RVec3* baseOffset,
	CollisionCollectorType collectorType,
	CastShapeResultCallback* callback, void* userData,
	BroadPhaseLayerFilter* broadPhaseLayerFilter,
	ObjectLayerFilter* objectLayerFilter,
	const BodyFilter* bodyFilter,
	const ShapeFilter* shapeFilter);

//--------------------------------------------------------------------------------------------------
// Body
//--------------------------------------------------------------------------------------------------
MOSS_API BodyID Body_GetID(const Body* body);
MOSS_API BodyType Body_GetBodyType(const Body* body);
MOSS_API bool Body_IsRigidBody(const Body* body);
MOSS_API bool Body_IsSoftBody(const Body* body);
MOSS_API bool Body_IsActive(const Body* body);
MOSS_API bool Body_IsStatic(const Body* body);
MOSS_API bool Body_IsKinematic(const Body* body);
MOSS_API bool Body_IsDynamic(const Body* body);
MOSS_API bool Body_CanBeKinematicOrDynamic(const Body* body);

MOSS_API void Body_SetIsSensor(Body* body, bool value);
MOSS_API bool Body_IsSensor(const Body* body);

MOSS_API void Body_SetCollideKinematicVsNonDynamic(Body* body, bool value);
MOSS_API bool Body_GetCollideKinematicVsNonDynamic(const Body* body);

MOSS_API void Body_SetUseManifoldReduction(Body* body, bool value);
MOSS_API bool Body_GetUseManifoldReduction(const Body* body);
MOSS_API bool Body_GetUseManifoldReductionWithBody(const Body* body, const Body* other);

MOSS_API void Body_SetApplyGyroscopicForce(Body* body, bool value);
MOSS_API bool Body_GetApplyGyroscopicForce(const Body* body);

MOSS_API void Body_SetEnhancedInternalEdgeRemoval(Body* body, bool value);
MOSS_API bool Body_GetEnhancedInternalEdgeRemoval(const Body* body);
MOSS_API bool Body_GetEnhancedInternalEdgeRemovalWithBody(const Body* body, const Body* other);

MOSS_API MotionType Body_GetMotionType(const Body* body);
MOSS_API void Body_SetMotionType(Body* body, MotionType motionType);

MOSS_API BroadPhaseLayer Body_GetBroadPhaseLayer(const Body* body);
MOSS_API ObjectLayer Body_GetObjectLayer(const Body* body);

MOSS_API void Body_GetCollisionGroup(const Body* body, CollisionGroup* result);
MOSS_API void Body_SetCollisionGroup(Body* body, const CollisionGroup* value);

MOSS_API bool Body_GetAllowSleeping(Body* body);
MOSS_API void Body_SetAllowSleeping(Body* body, bool allowSleeping);
MOSS_API void Body_ResetSleepTimer(Body* body);

MOSS_API float Body_GetFriction(const Body* body);
MOSS_API void Body_SetFriction(Body* body, float friction);
MOSS_API float Body_GetRestitution(const Body* body);
MOSS_API void Body_SetRestitution(Body* body, float restitution);
MOSS_API void Body_GetLinearVelocity(Body* body, Vec3* velocity);
MOSS_API void Body_SetLinearVelocity(Body* body, const Vec3* velocity);
MOSS_API void Body_SetLinearVelocityClamped(Body* body, const Vec3* velocity);
MOSS_API void Body_GetAngularVelocity(Body* body, Vec3* velocity);
MOSS_API void Body_SetAngularVelocity(Body* body, const Vec3* velocity);
MOSS_API void Body_SetAngularVelocityClamped(Body* body, const Vec3* velocity);

MOSS_API void Body_GetPointVelocityCOM(Body* body, const Vec3* pointRelativeToCOM, Vec3* velocity);
MOSS_API void Body_GetPointVelocity(Body* body, const RVec3* point, Vec3* velocity);

MOSS_API void Body_AddForce(Body* body, const Vec3* force);
MOSS_API void Body_AddForceAtPosition(Body* body, const Vec3* force, const RVec3* position);
MOSS_API void Body_AddTorque(Body* body, const Vec3* force);
MOSS_API void Body_GetAccumulatedForce(Body* body, Vec3* force);
MOSS_API void Body_GetAccumulatedTorque(Body* body, Vec3* force);
MOSS_API void Body_ResetForce(Body* body);
MOSS_API void Body_ResetTorque(Body* body);
MOSS_API void Body_ResetMotion(Body* body);

MOSS_API void Body_GetInverseInertia(Body* body, Matrix4x4* result);

MOSS_API void Body_AddImpulse(Body* body, const Vec3* impulse);
MOSS_API void Body_AddImpulseAtPosition(Body* body, const Vec3* impulse, const RVec3* position);
MOSS_API void Body_AddAngularImpulse(Body* body, const Vec3* angularImpulse);
MOSS_API void Body_MoveKinematic(Body* body, RVec3* targetPosition, Quat* targetRotation, float deltaTime);
MOSS_API bool Body_ApplyBuoyancyImpulse(Body* body, const RVec3* surfacePosition, const Vec3* surfaceNormal, float buoyancy, float linearDrag, float angularDrag, const Vec3* fluidVelocity, const Vec3* gravity, float deltaTime);

MOSS_API bool Body_IsInBroadPhase(Body* body);
MOSS_API bool Body_IsCollisionCacheInvalid(Body* body);

MOSS_API const Shape* Body_GetShape(Body* body);

MOSS_API void Body_GetPosition(const Body* body, RVec3* result);
MOSS_API void Body_GetRotation(const Body* body, Quat* result);
MOSS_API void Body_GetWorldTransform(const Body* body, RMatrix4x4* result);
MOSS_API void Body_GetCenterOfMassPosition(const Body* body, RVec3* result);
MOSS_API void Body_GetCenterOfMassTransform(const Body* body, RMatrix4x4* result);
MOSS_API void Body_GetInverseCenterOfMassTransform(const Body* body, RMatrix4x4* result);

MOSS_API void Body_GetWorldSpaceBounds(const Body* body, AABB3* result);
MOSS_API void Body_GetWorldSpaceSurfaceNormal(const Body* body, SubShapeID subShapeID, const RVec3* position, Vec3* normal);

MOSS_API MotionProperties* Body_GetMotionProperties(Body* body);
MOSS_API MotionProperties* Body_GetMotionPropertiesUnchecked(Body* body);

MOSS_API void Body_SetUserData(Body* body, uint64_t userData);
MOSS_API uint64_t Body_GetUserData(Body* body);

MOSS_API Body* Body_GetFixedToWorldBody(void);

/* BroadPhaseLayerFilter_Procs */
typedef struct BroadPhaseLayerFilter_Procs {
	bool(API_CALL* ShouldCollide)(void* userData, BroadPhaseLayer layer);
} BroadPhaseLayerFilter_Procs;

MOSS_API void BroadPhaseLayerFilter_SetProcs(const BroadPhaseLayerFilter_Procs* procs);
MOSS_API BroadPhaseLayerFilter* BroadPhaseLayerFilter_Create(void* userData);
MOSS_API void BroadPhaseLayerFilter_Destroy(BroadPhaseLayerFilter* filter);

/* ObjectLayerFilter */
typedef struct ObjectLayerFilter_Procs {
	bool(API_CALL* ShouldCollide)(void* userData, ObjectLayer layer);
} ObjectLayerFilter_Procs;

MOSS_API void ObjectLayerFilter_SetProcs(const ObjectLayerFilter_Procs* procs);
MOSS_API ObjectLayerFilter* ObjectLayerFilter_Create(void* userData);
MOSS_API void ObjectLayerFilter_Destroy(ObjectLayerFilter* filter);

/* BodyFilter */
typedef struct BodyFilter_Procs {
	bool(API_CALL* ShouldCollide)(void* userData, BodyID bodyID);
	bool(API_CALL* ShouldCollideLocked)(void* userData, const Body* bodyID);
} BodyFilter_Procs;

MOSS_API void BodyFilter_SetProcs(const BodyFilter_Procs* procs);
MOSS_API BodyFilter* BodyFilter_Create(void* userData);
MOSS_API void BodyFilter_Destroy(BodyFilter* filter);

/* ShapeFilter */
typedef struct ShapeFilter_Procs {
	bool(API_CALL* ShouldCollide)(void* userData, const Shape* shape2, const SubShapeID* subShapeIDOfShape2);
	bool(API_CALL* ShouldCollide2)(void* userData, const Shape* shape1, const SubShapeID* subShapeIDOfShape1, const Shape* shape2, const SubShapeID* subShapeIDOfShape2);
} ShapeFilter_Procs;

MOSS_API void ShapeFilter_SetProcs(const ShapeFilter_Procs* procs);
MOSS_API ShapeFilter* ShapeFilter_Create(void* userData);
MOSS_API void ShapeFilter_Destroy(ShapeFilter* filter);
MOSS_API BodyID ShapeFilter_GetBodyID2(ShapeFilter* filter);
MOSS_API void ShapeFilter_SetBodyID2(ShapeFilter* filter, BodyID id);

/* SimShapeFilter */
typedef struct SimShapeFilter_Procs {
	bool(API_CALL* ShouldCollide)(void* userData, 
		const Body* body1, 
		const Shape* shape1, 
		const SubShapeID* subShapeIDOfShape1,
		const Body* body2,
		const Shape* shape2, 
		const SubShapeID* subShapeIDOfShape2
		);
} SimShapeFilter_Procs;

MOSS_API void SimShapeFilter_SetProcs(const SimShapeFilter_Procs* procs);
MOSS_API SimShapeFilter* SimShapeFilter_Create(void* userData);
MOSS_API void SimShapeFilter_Destroy(SimShapeFilter* filter);

/* Contact listener */
typedef struct ContactListener_Procs {
	ValidateResult(API_CALL* OnContactValidate)(void* userData,
		const Body* body1,
		const Body* body2,
		const RVec3* baseOffset,
		const CollideShapeResult* collisionResult);

	void(API_CALL* OnContactAdded)(void* userData,
		const Body* body1,
		const Body* body2,
		const ContactManifold* manifold,
		ContactSettings* settings);

	void(API_CALL* OnContactPersisted)(void* userData,
		const Body* body1,
		const Body* body2,
		const ContactManifold* manifold,
		ContactSettings* settings);

	void(API_CALL* OnContactRemoved)(void* userData,
		const SubShapeIDPair* subShapePair
		);
} ContactListener_Procs;

MOSS_API void ContactListener_SetProcs(const ContactListener_Procs* procs);
MOSS_API ContactListener* ContactListener_Create(void* userData);
MOSS_API void ContactListener_Destroy(ContactListener* listener);

/* BodyActivationListener */
typedef struct BodyActivationListener_Procs {
	void(API_CALL* OnBodyActivated)(void* userData, BodyID bodyID, uint64_t bodyUserData);
	void(API_CALL* OnBodyDeactivated)(void* userData, BodyID bodyID, uint64_t bodyUserData);
} BodyActivationListener_Procs;

MOSS_API void BodyActivationListener_SetProcs(const BodyActivationListener_Procs* procs);
MOSS_API BodyActivationListener* BodyActivationListener_Create(void* userData);
MOSS_API void BodyActivationListener_Destroy(BodyActivationListener* listener);

/* BodyDrawFilter */
typedef struct BodyDrawFilter_Procs {
	bool(API_CALL* ShouldDraw)(void* userData, const Body* body);
} BodyDrawFilter_Procs;

MOSS_API void BodyDrawFilter_SetProcs(const BodyDrawFilter_Procs* procs);
MOSS_API BodyDrawFilter* BodyDrawFilter_Create(void* userData);
MOSS_API void BodyDrawFilter_Destroy(BodyDrawFilter* filter);

/* ContactManifold */
MOSS_API void ContactManifold_GetWorldSpaceNormal(const ContactManifold* manifold, Vec3* result);
MOSS_API float ContactManifold_GetPenetrationDepth(const ContactManifold* manifold);
MOSS_API SubShapeID ContactManifold_GetSubShapeID1(const ContactManifold* manifold);
MOSS_API SubShapeID ContactManifold_GetSubShapeID2(const ContactManifold* manifold);
MOSS_API uint32_t ContactManifold_GetPointCount(const ContactManifold* manifold);
MOSS_API void ContactManifold_GetWorldSpaceContactPointOn1(const ContactManifold* manifold, uint32_t index, RVec3* result);
MOSS_API void ContactManifold_GetWorldSpaceContactPointOn2(const ContactManifold* manifold, uint32_t index, RVec3* result);

/* CharacterBase */
MOSS_API void CharacterBase_Destroy(CharacterBase* character);
MOSS_API float CharacterBase_GetCosMaxSlopeAngle(CharacterBase* character);
MOSS_API void CharacterBase_SetMaxSlopeAngle(CharacterBase* character, float maxSlopeAngle);
MOSS_API void CharacterBase_GetUp(CharacterBase* character, Vec3* result);
MOSS_API void CharacterBase_SetUp(CharacterBase* character, const Vec3* value);
MOSS_API bool CharacterBase_IsSlopeTooSteep(CharacterBase* character, const Vec3* value);
MOSS_API const Shape* CharacterBase_GetShape(CharacterBase* character);

MOSS_API GroundState CharacterBase_GetGroundState(CharacterBase* character);
MOSS_API bool CharacterBase_IsSupported(CharacterBase* character);
MOSS_API void CharacterBase_GetGroundPosition(CharacterBase* character, RVec3* position);
MOSS_API void CharacterBase_GetGroundNormal(CharacterBase* character, Vec3* normal);
MOSS_API void CharacterBase_GetGroundVelocity(CharacterBase* character, Vec3* velocity);
MOSS_API const PhysicsMaterial* CharacterBase_GetGroundMaterial(CharacterBase* character);
MOSS_API BodyID CharacterBase_GetGroundBodyId(CharacterBase* character);
MOSS_API SubShapeID CharacterBase_GetGroundSubShapeId(CharacterBase* character);
MOSS_API uint64_t CharacterBase_GetGroundUserData(CharacterBase* character);

/* CharacterSettings */
MOSS_API void CharacterSettings_Init(CharacterSettings* settings);

/* Character */
MOSS_API Character* Character_Create(const CharacterSettings* settings,
	const RVec3* position,
	const Quat* rotation,
	uint64_t userData,
	PhysicsSystem* system);

MOSS_API void Character_AddToPhysicsSystem(Character* character, Activation activationMode /*= ActivationActivate */, bool lockBodies /* = true */);
MOSS_API void Character_RemoveFromPhysicsSystem(Character* character, bool lockBodies /* = true */);
MOSS_API void Character_Activate(Character* character, bool lockBodies /* = true */);
MOSS_API void Character_PostSimulation(Character* character, float maxSeparationDistance, bool lockBodies /* = true */);
MOSS_API void Character_SetLinearAndAngularVelocity(Character* character, Vec3* linearVelocity, Vec3* angularVelocity, bool lockBodies /* = true */);
MOSS_API void Character_GetLinearVelocity(Character* character, Vec3* result);
MOSS_API void Character_SetLinearVelocity(Character* character, const Vec3* value, bool lockBodies /* = true */);
MOSS_API void Character_AddLinearVelocity(Character* character, const Vec3* value, bool lockBodies /* = true */);
MOSS_API void Character_AddImpulse(Character* character, const Vec3* value, bool lockBodies /* = true */);
MOSS_API BodyID Character_GetBodyID(const Character* character);

MOSS_API void Character_GetPositionAndRotation(Character* character, RVec3* position, Quat* rotation, bool lockBodies /* = true */);
MOSS_API void Character_SetPositionAndRotation(Character* character, const RVec3* position, const Quat* rotation, Activation activationMode, bool lockBodies /* = true */);
MOSS_API void Character_GetPosition(Character* character, RVec3* position, bool lockBodies /* = true */);
MOSS_API void Character_SetPosition(Character* character, const RVec3* position, Activation activationMode, bool lockBodies /* = true */);
MOSS_API void Character_GetRotation(Character* character, Quat* rotation, bool lockBodies /* = true */);
MOSS_API void Character_SetRotation(Character* character, const Quat* rotation, Activation activationMode, bool lockBodies /* = true */);
MOSS_API void Character_GetCenterOfMassPosition(Character* character, RVec3* result, bool lockBodies /* = true */);
MOSS_API void Character_GetWorldTransform(Character* character, RMatrix4x4* result, bool lockBodies /* = true */);
MOSS_API ObjectLayer Character_GetLayer(const Character* character);
MOSS_API void Character_SetLayer(Character* character, ObjectLayer value, bool lockBodies /*= true*/);
MOSS_API void Character_SetShape(Character* character, const Shape* shape, float maxPenetrationDepth, bool lockBodies /*= true*/);

/* CharacterVirtualSettings */
MOSS_API void CharacterVirtualSettings_Init(CharacterVirtualSettings* settings);

/* CharacterVirtual */
MOSS_API CharacterVirtual* CharacterVirtual_Create(const CharacterVirtualSettings* settings,
	const RVec3* position,
	const Quat* rotation,
	uint64_t userData,
	PhysicsSystem* system);

MOSS_API CharacterID CharacterVirtual_GetID(const CharacterVirtual* character);
MOSS_API void CharacterVirtual_SetListener(CharacterVirtual* character, CharacterContactListener* listener);
MOSS_API void CharacterVirtual_SetCharacterVsCharacterCollision(CharacterVirtual* character, CharacterVsCharacterCollision* characterVsCharacterCollision);

MOSS_API void CharacterVirtual_GetLinearVelocity(CharacterVirtual* character, Vec3* velocity);
MOSS_API void CharacterVirtual_SetLinearVelocity(CharacterVirtual* character, const Vec3* velocity);
MOSS_API void CharacterVirtual_GetPosition(CharacterVirtual* character, RVec3* position);
MOSS_API void CharacterVirtual_SetPosition(CharacterVirtual* character, const RVec3* position);
MOSS_API void CharacterVirtual_GetRotation(CharacterVirtual* character, Quat* rotation);
MOSS_API void CharacterVirtual_SetRotation(CharacterVirtual* character, const Quat* rotation);
MOSS_API void CharacterVirtual_GetWorldTransform(CharacterVirtual* character, RMatrix4x4* result);
MOSS_API void CharacterVirtual_GetCenterOfMassTransform(CharacterVirtual* character, RMatrix4x4* result);
MOSS_API float CharacterVirtual_GetMass(CharacterVirtual* character);
MOSS_API void CharacterVirtual_SetMass(CharacterVirtual* character, float value);
MOSS_API float CharacterVirtual_GetMaxStrength(CharacterVirtual* character);
MOSS_API void CharacterVirtual_SetMaxStrength(CharacterVirtual* character, float value);

MOSS_API float CharacterVirtual_GetPenetrationRecoverySpeed(CharacterVirtual* character);
MOSS_API void CharacterVirtual_SetPenetrationRecoverySpeed(CharacterVirtual* character, float value);
MOSS_API bool	CharacterVirtual_GetEnhancedInternalEdgeRemoval(CharacterVirtual* character);
MOSS_API void CharacterVirtual_SetEnhancedInternalEdgeRemoval(CharacterVirtual* character, bool value);
MOSS_API float CharacterVirtual_GetCharacterPadding(CharacterVirtual* character);
MOSS_API uint32_t CharacterVirtual_GetMaxNumHits(CharacterVirtual* character);
MOSS_API void CharacterVirtual_SetMaxNumHits(CharacterVirtual* character, uint32_t value);
MOSS_API float CharacterVirtual_GetHitReductionCosMaxAngle(CharacterVirtual* character);
MOSS_API void CharacterVirtual_SetHitReductionCosMaxAngle(CharacterVirtual* character, float value);
MOSS_API bool CharacterVirtual_GetMaxHitsExceeded(CharacterVirtual* character);
MOSS_API void CharacterVirtual_GetShapeOffset(CharacterVirtual* character, Vec3* result);
MOSS_API void CharacterVirtual_SetShapeOffset(CharacterVirtual* character, const Vec3* value);
MOSS_API uint64_t CharacterVirtual_GetUserData(const CharacterVirtual* character);
MOSS_API void CharacterVirtual_SetUserData(CharacterVirtual* character, uint64_t value);
MOSS_API BodyID CharacterVirtual_GetInnerBodyID(const CharacterVirtual* character);

MOSS_API void CharacterVirtual_CancelVelocityTowardsSteepSlopes(CharacterVirtual* character, const Vec3* desiredVelocity, Vec3* velocity);
MOSS_API void CharacterVirtual_StartTrackingContactChanges(CharacterVirtual* character);
MOSS_API void CharacterVirtual_FinishTrackingContactChanges(CharacterVirtual* character);
MOSS_API void CharacterVirtual_Update(CharacterVirtual* character, float deltaTime, ObjectLayer layer, PhysicsSystem* system, const BodyFilter* bodyFilter, const ShapeFilter* shapeFilter);

MOSS_API void CharacterVirtual_ExtendedUpdate(CharacterVirtual* character, float deltaTime,
	const ExtendedUpdateSettings* settings, ObjectLayer layer, PhysicsSystem* system, const BodyFilter* bodyFilter, const ShapeFilter* shapeFilter);
MOSS_API void CharacterVirtual_RefreshContacts(CharacterVirtual* character, ObjectLayer layer, PhysicsSystem* system, const BodyFilter* bodyFilter, const ShapeFilter* shapeFilter);

MOSS_API bool CharacterVirtual_CanWalkStairs(CharacterVirtual* character, const Vec3* linearVelocity);
MOSS_API bool CharacterVirtual_WalkStairs(CharacterVirtual* character, float deltaTime,
	const Vec3* stepUp, const Vec3* stepForward, const Vec3* stepForwardTest, const Vec3* stepDownExtra,
	ObjectLayer layer, PhysicsSystem* system,
	const BodyFilter* bodyFilter, const ShapeFilter* shapeFilter);

MOSS_API bool CharacterVirtual_StickToFloor(CharacterVirtual* character, const Vec3* stepDown,
	ObjectLayer layer, PhysicsSystem* system,
	const BodyFilter* bodyFilter, const ShapeFilter* shapeFilter);

MOSS_API void CharacterVirtual_UpdateGroundVelocity(CharacterVirtual* character);
MOSS_API bool CharacterVirtual_SetShape(CharacterVirtual* character, const Shape* shape, float maxPenetrationDepth, ObjectLayer layer, PhysicsSystem* system, const BodyFilter* bodyFilter, const ShapeFilter* shapeFilter);
MOSS_API void CharacterVirtual_SetInnerBodyShape(CharacterVirtual* character, const Shape* shape);

MOSS_API uint32_t CharacterVirtual_GetNumActiveContacts(CharacterVirtual* character);
MOSS_API void CharacterVirtual_GetActiveContact(CharacterVirtual* character, uint32_t index, CharacterVirtualContact* result);

MOSS_API bool CharacterVirtual_HasCollidedWithBody(CharacterVirtual* character, const BodyID body);
MOSS_API bool CharacterVirtual_HasCollidedWith(CharacterVirtual* character, const CharacterID other);
MOSS_API bool CharacterVirtual_HasCollidedWithCharacter(CharacterVirtual* character, const CharacterVirtual* other);

/* CharacterContactListener */
typedef struct CharacterContactListener_Procs {
	void (API_CALL* OnAdjustBodyVelocity)(void* userData,
		const CharacterVirtual* character,
		const Body* body2,
		Vec3* ioLinearVelocity,
		Vec3* ioAngularVelocity);

	bool(API_CALL* OnContactValidate)(void* userData,
		const CharacterVirtual* character,
		const BodyID bodyID2,
		const SubShapeID subShapeID2);

	bool(API_CALL* OnCharacterContactValidate)(void* userData,
		const CharacterVirtual* character,
		const CharacterVirtual* otherCharacter,
		const SubShapeID subShapeID2);

	void(API_CALL* OnContactAdded)(void* userData,
		const CharacterVirtual* character,
		const BodyID bodyID2,
		const SubShapeID subShapeID2,
		const RVec3* contactPosition,
		const Vec3* contactNormal,
		CharacterContactSettings* ioSettings);

	void(API_CALL* OnContactPersisted)(void* userData,
		const CharacterVirtual* character,
		const BodyID bodyID2,
		const SubShapeID subShapeID2,
		const RVec3* contactPosition,
		const Vec3* contactNormal,
		CharacterContactSettings* ioSettings);

	void(API_CALL* OnContactRemoved)(void* userData,
		const CharacterVirtual* character,
		const BodyID bodyID2,
		const SubShapeID subShapeID2);

	void(API_CALL* OnCharacterContactAdded)(void* userData,
		const CharacterVirtual* character,
		const CharacterVirtual* otherCharacter,
		const SubShapeID subShapeID2,
		const RVec3* contactPosition,
		const Vec3* contactNormal,
		CharacterContactSettings* ioSettings);

	void(API_CALL* OnCharacterContactPersisted)(void* userData,
		const CharacterVirtual* character,
		const CharacterVirtual* otherCharacter,
		const SubShapeID subShapeID2,
		const RVec3* contactPosition,
		const Vec3* contactNormal,
		CharacterContactSettings* ioSettings);

	void(API_CALL* OnCharacterContactRemoved)(void* userData,
		const CharacterVirtual* character,
		const CharacterID otherCharacterID,
		const SubShapeID subShapeID2);

	void(API_CALL* OnContactSolve)(void* userData,
		const CharacterVirtual* character,
		const BodyID bodyID2,
		const SubShapeID subShapeID2,
		const RVec3* contactPosition,
		const Vec3* contactNormal,
		const Vec3* contactVelocity,
		const PhysicsMaterial* contactMaterial,
		const Vec3* characterVelocity,
		Vec3* newCharacterVelocity
		);

	void(API_CALL* OnCharacterContactSolve)(void* userData,
		const CharacterVirtual* character,
		const CharacterVirtual* otherCharacter,
		const SubShapeID subShapeID2,
		const RVec3* contactPosition,
		const Vec3* contactNormal,
		const Vec3* contactVelocity,
		const PhysicsMaterial* contactMaterial,
		const Vec3* characterVelocity,
		Vec3* newCharacterVelocity
		);
} CharacterContactListener_Procs;

MOSS_API void CharacterContactListener_SetProcs(const CharacterContactListener_Procs* procs);
MOSS_API CharacterContactListener* CharacterContactListener_Create(void* userData);
MOSS_API void CharacterContactListener_Destroy(CharacterContactListener* listener);

/* CharacterVsCharacterCollision */
typedef struct CharacterVsCharacterCollision_Procs {
	void (API_CALL* CollideCharacter)(void* userData,
		const CharacterVirtual* character,
		const RMatrix4x4* centerOfMassTransform,
		const CollideShapeSettings* collideShapeSettings,
		const RVec3* baseOffset
		);

	void (API_CALL* CastCharacter)(void* userData,
		const CharacterVirtual* character,
		const RMatrix4x4* centerOfMassTransform,
		const Vec3* direction,
		const ShapeCastSettings* shapeCastSettings,
		const RVec3* baseOffset
		);
} CharacterVsCharacterCollision_Procs;

MOSS_API void CharacterVsCharacterCollision_SetProcs(const CharacterVsCharacterCollision_Procs* procs);
MOSS_API CharacterVsCharacterCollision* CharacterVsCharacterCollision_Create(void* userData);
MOSS_API CharacterVsCharacterCollision* CharacterVsCharacterCollision_CreateSimple(void);
MOSS_API void CharacterVsCharacterCollisionSimple_AddCharacter(CharacterVsCharacterCollision* characterVsCharacter, CharacterVirtual* character);
MOSS_API void CharacterVsCharacterCollisionSimple_RemoveCharacter(CharacterVsCharacterCollision* characterVsCharacter, CharacterVirtual* character);
MOSS_API void CharacterVsCharacterCollision_Destroy(CharacterVsCharacterCollision* listener);

/* CollisionDispatch */
MOSS_API bool CollisionDispatch_CollideShapeVsShape(
	const Shape* shape1, const Shape* shape2,
	const Vec3* scale1, const Vec3* scale2,
	const Matrix4x4* centerOfMassTransform1, const Matrix4x4* centerOfMassTransform2,
	const CollideShapeSettings* collideShapeSettings,
	CollideShapeCollectorCallback* callback, void* userData, const ShapeFilter* shapeFilter);

MOSS_API bool CollisionDispatch_CastShapeVsShapeLocalSpace(
	const Vec3* direction, const Shape* shape1, const Shape* shape2,
	const Vec3* scale1InShape2LocalSpace, const Vec3* scale2,
	Matrix4x4* centerOfMassTransform1InShape2LocalSpace, Matrix4x4* centerOfMassWorldTransform2,
	const ShapeCastSettings* shapeCastSettings,
	CastShapeCollectorCallback* callback, void* userData,
	const ShapeFilter* shapeFilter);

MOSS_API bool CollisionDispatch_CastShapeVsShapeWorldSpace(
	const Vec3* direction, const Shape* shape1, const Shape* shape2,
	const Vec3* scale1, const Vec3* inScale2,
	const Matrix4x4* centerOfMassWorldTransform1, const Matrix4x4* centerOfMassWorldTransform2,
	const ShapeCastSettings* shapeCastSettings,
	CastShapeCollectorCallback* callback, void* userData,
	const ShapeFilter* shapeFilter);

/* DebugRenderer */
typedef struct DebugRenderer_Procs {
	void (API_CALL* DrawLine)(void* userData, const RVec3* from, const RVec3* to, Color color);
	void (API_CALL* DrawTriangle)(void* userData, const RVec3* v1, const RVec3* v2, const RVec3* v3, Color color, DebugRenderer_CastShadow castShadow);
	void (API_CALL* DrawText3D)(void* userData, const RVec3* position, const char* str, Color color, float height);
} DebugRenderer_Procs;

MOSS_API void DebugRenderer_SetProcs(const DebugRenderer_Procs* procs);
MOSS_API DebugRenderer* DebugRenderer_Create(void* userData);
MOSS_API void DebugRenderer_Destroy(DebugRenderer* renderer);
MOSS_API void DebugRenderer_NextFrame(DebugRenderer* renderer);
MOSS_API void DebugRenderer_SetCameraPos(DebugRenderer* renderer, const RVec3* position);

MOSS_API void DebugRenderer_DrawLine(DebugRenderer* renderer, const RVec3* from, const RVec3* to, Color color);
MOSS_API void DebugRenderer_DrawWireBox(DebugRenderer* renderer, const AABB3* box, Color color);
MOSS_API void DebugRenderer_DrawWireBox2(DebugRenderer* renderer, const RMatrix4x4* matrix, const AABB3* box, Color color);
MOSS_API void DebugRenderer_DrawMarker(DebugRenderer* renderer, const RVec3* position, Color color, float size);
MOSS_API void DebugRenderer_DrawArrow(DebugRenderer* renderer, const RVec3* from, const RVec3* to, Color color, float size);
MOSS_API void DebugRenderer_DrawCoordinateSystem(DebugRenderer* renderer, const RMatrix4x4* matrix, float size);
MOSS_API void DebugRenderer_DrawPlane(DebugRenderer* renderer, const RVec3* point, const Vec3* normal, Color color, float size);
MOSS_API void DebugRenderer_DrawWireTriangle(DebugRenderer* renderer, const RVec3* v1, const RVec3* v2, const RVec3* v3, Color color);
MOSS_API void DebugRenderer_DrawWireSphere(DebugRenderer* renderer, const RVec3* center, float radius, Color color, int level);
MOSS_API void DebugRenderer_DrawWireUnitSphere(DebugRenderer* renderer, const RMatrix4x4* matrix, Color color, int level);
MOSS_API void DebugRenderer_DrawTriangle(DebugRenderer* renderer, const RVec3* v1, const RVec3* v2, const RVec3* v3, Color color, DebugRenderer_CastShadow castShadow);
MOSS_API void DebugRenderer_DrawBox(DebugRenderer* renderer, const AABB3* box, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawBox2(DebugRenderer* renderer, const RMatrix4x4* matrix, const AABB3* box, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawSphere(DebugRenderer* renderer, const RVec3* center, float radius, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawUnitSphere(DebugRenderer* renderer, RMatrix4x4 matrix, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawCapsule(DebugRenderer* renderer, const RMatrix4x4* matrix, float halfHeightOfCylinder, float radius, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawCylinder(DebugRenderer* renderer, const RMatrix4x4* matrix, float halfHeight, float radius, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawOpenCone(DebugRenderer* renderer, const RVec3* top, const Vec3* axis, const Vec3* perpendicular, float halfAngle, float length, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawSwingConeLimits(DebugRenderer* renderer, const RMatrix4x4* matrix, float swingYHalfAngle, float swingZHalfAngle, float edgeLength, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawSwingPyramidLimits(DebugRenderer* renderer, const RMatrix4x4* matrix, float minSwingYAngle, float maxSwingYAngle, float minSwingZAngle, float maxSwingZAngle, float edgeLength, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawPie(DebugRenderer* renderer, const RVec3* center, float radius, const Vec3* normal, const Vec3* axis, float minAngle, float maxAngle, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);
MOSS_API void DebugRenderer_DrawTaperedCylinder(DebugRenderer* renderer, const RMatrix4x4* inMatrix, float top, float bottom, float topRadius, float bottomRadius, Color color, DebugRenderer_CastShadow castShadow, DebugRenderer_DrawMode drawMode);


/* Skeleton */
typedef struct SkeletonJoint {
	const char*		name;
	const char*		parentName;
	int				parentJointIndex;
} SkeletonJoint;

MOSS_API Skeleton* Skeleton_Create(void);
MOSS_API void Skeleton_Destroy(Skeleton* skeleton);

MOSS_API uint32_t Skeleton_AddJoint(Skeleton* skeleton, const char* name);
MOSS_API uint32_t Skeleton_AddJoint2(Skeleton* skeleton, const char* name, int parentIndex);
MOSS_API uint32_t Skeleton_AddJoint3(Skeleton* skeleton, const char* name, const char* parentName);
MOSS_API int Skeleton_GetJointCount(const Skeleton* skeleton);
MOSS_API void Skeleton_GetJoint(const Skeleton* skeleton, int index, SkeletonJoint* joint);
MOSS_API int Skeleton_GetJointIndex(const Skeleton* skeleton, const char* name);
MOSS_API void Skeleton_CalculateParentJointIndices(Skeleton* skeleton);
MOSS_API bool Skeleton_AreJointsCorrectlyOrdered(const Skeleton* skeleton);

/* Ragdoll */
MOSS_API RagdollSettings* RagdollSettings_Create(void);
MOSS_API void RagdollSettings_Destroy(RagdollSettings* settings);

MOSS_API const Skeleton* RagdollSettings_GetSkeleton(const RagdollSettings* character);
MOSS_API void RagdollSettings_SetSkeleton(RagdollSettings* character, Skeleton* skeleton);
MOSS_API bool RagdollSettings_Stabilize(RagdollSettings* settings);
MOSS_API void RagdollSettings_DisableParentChildCollisions(RagdollSettings* settings, const Matrix4x4* jointMatrices /*=nullptr*/, float minSeparationDistance/* = 0.0f*/);
MOSS_API void RagdollSettings_CalculateBodyIndexToConstraintIndex(RagdollSettings* settings);
MOSS_API int RagdollSettings_GetConstraintIndexForBodyIndex(RagdollSettings* settings, int bodyIndex);
MOSS_API void RagdollSettings_CalculateConstraintIndexToBodyIdxPair(RagdollSettings* settings);

MOSS_API Ragdoll* RagdollSettings_CreateRagdoll(RagdollSettings* settings, PhysicsSystem* system, CollisionGroupID collisionGroup /*=0*/, uint64_t userData/* = 0*/);
MOSS_API void Ragdoll_Destroy(Ragdoll* ragdoll);
MOSS_API void Ragdoll_AddToPhysicsSystem(Ragdoll* ragdoll, Activation activationMode /*= ActivationActivate */, bool lockBodies /* = true */);
MOSS_API void Ragdoll_RemoveFromPhysicsSystem(Ragdoll* ragdoll, bool lockBodies /* = true */);
MOSS_API void Ragdoll_Activate(Ragdoll* ragdoll, bool lockBodies /* = true */);
MOSS_API bool Ragdoll_IsActive(const Ragdoll* ragdoll, bool lockBodies /* = true */);
MOSS_API void Ragdoll_ResetWarmStart(Ragdoll* ragdoll);

/* EstimateCollisionResponse */
MOSS_API void EstimateCollisionResponse(const Body* body1, const Body* body2, const ContactManifold* manifold, float combinedFriction, float combinedRestitution, float minVelocityForRestitution, uint32_t numIterations, CollisionEstimationResult* result);

/* Vehicle */
typedef struct WheelSettings						WheelSettings;
typedef struct WheelSettingsWV						WheelSettingsWV;	/* Inherits WheelSettings */
typedef struct WheelSettingsTV						WheelSettingsTV;	/* Inherits WheelSettings */

typedef struct Wheel								Wheel;
typedef struct WheelWV								WheelWV;			/* Inherits Wheel */
typedef struct WheelTV								WheelTV;			/* Inherits Wheel */

typedef struct VehicleTransmissionSettings			VehicleTransmissionSettings;
typedef struct VehicleCollisionTester				VehicleCollisionTester;
typedef struct VehicleCollisionTesterRay			VehicleCollisionTesterRay;			/* Inherits VehicleCollisionTester */
typedef struct VehicleCollisionTesterCastSphere		VehicleCollisionTesterCastSphere;	/* Inherits VehicleCollisionTester */
typedef struct VehicleCollisionTesterCastCylinder	VehicleCollisionTesterCastCylinder;	/* Inherits VehicleCollisionTester */
typedef struct VehicleConstraint					VehicleConstraint;					/* Inherits Constraint */

typedef struct VehicleControllerSettings			VehicleControllerSettings;
typedef struct WheeledVehicleControllerSettings		WheeledVehicleControllerSettings;	/* Inherits VehicleControllerSettings */
typedef struct MotorcycleControllerSettings			MotorcycleControllerSettings;		/* Inherits WheeledVehicleControllerSettings */
typedef struct TrackedVehicleControllerSettings		TrackedVehicleControllerSettings;	/* Inherits VehicleControllerSettings */

typedef struct WheeledVehicleController				WheeledVehicleController;	/* Inherits VehicleController */
typedef struct MotorcycleController					MotorcycleController;		/* Inherits WheeledVehicleController */
typedef struct TrackedVehicleController				TrackedVehicleController;	/* Inherits VehicleController */

typedef struct VehicleController					VehicleController;

typedef struct VehicleAntiRollBar {
	int						leftWheel;
	int						rightWheel;
	float					stiffness;
} VehicleAntiRollBar;

typedef struct VehicleConstraintSettings {
	ConstraintSettings			base;    /* Inherits ConstraintSettings */

	Vec3						up;
	Vec3						forward;
	float							maxPitchRollAngle;
	uint32_t						wheelsCount;
	WheelSettings**				wheels;
	uint32_t						antiRollBarsCount;
	const VehicleAntiRollBar*	antiRollBars;
	VehicleControllerSettings*	controller;
} VehicleConstraintSettings;

typedef struct VehicleEngineSettings {
	float					maxTorque;
	float					minRPM;
	float					maxRPM;
	//LinearCurve			normalizedTorque;
	float					inertia;
	float					angularDamping;
} VehicleEngineSettings;

typedef struct VehicleDifferentialSettings {
	int		leftWheel;
	int		rightWheel;
	float	differentialRatio;
	float	leftRightSplit;
	float	limitedSlipRatio;
	float	engineTorqueRatio;
} VehicleDifferentialSettings;

MOSS_API void VehicleConstraintSettings_Init(VehicleConstraintSettings* settings);

MOSS_API VehicleConstraint* VehicleConstraint_Create(Body* body, const VehicleConstraintSettings* settings);
MOSS_API PhysicsStepListener* VehicleConstraint_AsPhysicsStepListener(VehicleConstraint* constraint);

MOSS_API void VehicleConstraint_SetMaxPitchRollAngle(VehicleConstraint* constraint, float maxPitchRollAngle);
MOSS_API void VehicleConstraint_SetVehicleCollisionTester(VehicleConstraint* constraint, const VehicleCollisionTester* tester);

MOSS_API void VehicleConstraint_OverrideGravity(VehicleConstraint* constraint, const Vec3* value);
MOSS_API bool VehicleConstraint_IsGravityOverridden(const VehicleConstraint* constraint);
MOSS_API void VehicleConstraint_GetGravityOverride(const VehicleConstraint* constraint, Vec3* result);
MOSS_API void VehicleConstraint_ResetGravityOverride(VehicleConstraint* constraint);

MOSS_API void VehicleConstraint_GetLocalForward(const VehicleConstraint* constraint, Vec3* result);
MOSS_API void VehicleConstraint_GetLocalUp(const VehicleConstraint* constraint, Vec3* result);
MOSS_API void VehicleConstraint_GetWorldUp(const VehicleConstraint* constraint, Vec3* result);

MOSS_API const Body* VehicleConstraint_GetVehicleBody(const VehicleConstraint* constraint);
MOSS_API VehicleController* VehicleConstraint_GetController(VehicleConstraint* constraint);
MOSS_API uint32_t VehicleConstraint_GetWheelsCount(VehicleConstraint* constraint);
MOSS_API Wheel* VehicleConstraint_GetWheel(VehicleConstraint* constraint, uint32_t index);
MOSS_API void VehicleConstraint_GetWheelLocalBasis(VehicleConstraint* constraint, const Wheel* wheel, Vec3* outForward, Vec3* outUp, Vec3* outRight);
MOSS_API void VehicleConstraint_GetWheelLocalTransform(VehicleConstraint* constraint, uint32_t wheelIndex, const Vec3* wheelRight, const Vec3* wheelUp, Matrix4x4* result);
MOSS_API void VehicleConstraint_GetWheelWorldTransform(VehicleConstraint* constraint, uint32_t wheelIndex, const Vec3* wheelRight, const Vec3* wheelUp, RMatrix4x4* result);

/* Wheel */
MOSS_API WheelSettings* WheelSettings_Create(void);
MOSS_API void WheelSettings_Destroy(WheelSettings* settings);
MOSS_API void WheelSettings_GetPosition(const WheelSettings* settings, Vec3* result);
MOSS_API void WheelSettings_SetPosition(WheelSettings* settings, const Vec3* value);
MOSS_API void WheelSettings_GetSuspensionForcePoint(const WheelSettings* settings, Vec3* result);
MOSS_API void WheelSettings_SetSuspensionForcePoint(WheelSettings* settings, const Vec3* value);
MOSS_API void WheelSettings_GetSuspensionDirection(const WheelSettings* settings, Vec3* result);
MOSS_API void WheelSettings_SetSuspensionDirection(WheelSettings* settings, const Vec3* value);
MOSS_API void WheelSettings_GetSteeringAxis(const WheelSettings* settings, Vec3* result);
MOSS_API void WheelSettings_SetSteeringAxis(WheelSettings* settings, const Vec3* value);
MOSS_API void WheelSettings_GetWheelUp(const WheelSettings* settings, Vec3* result);
MOSS_API void WheelSettings_SetWheelUp(WheelSettings* settings, const Vec3* value);
MOSS_API void WheelSettings_GetWheelForward(const WheelSettings* settings, Vec3* result);
MOSS_API void WheelSettings_SetWheelForward(WheelSettings* settings, const Vec3* value);
MOSS_API float WheelSettings_GetSuspensionMinLength(const WheelSettings* settings);
MOSS_API void WheelSettings_SetSuspensionMinLength(WheelSettings* settings, float value);
MOSS_API float WheelSettings_GetSuspensionMaxLength(const WheelSettings* settings);
MOSS_API void WheelSettings_SetSuspensionMaxLength(WheelSettings* settings, float value);
MOSS_API float WheelSettings_GetSuspensionPreloadLength(const WheelSettings* settings);
MOSS_API void WheelSettings_SetSuspensionPreloadLength(WheelSettings* settings, float value);
MOSS_API void WheelSettings_GetSuspensionSpring(const WheelSettings* settings, SpringSettings* result);
MOSS_API void WheelSettings_SetSuspensionSpring(WheelSettings* settings, SpringSettings* springSettings);
MOSS_API float WheelSettings_GetRadius(const WheelSettings* settings);
MOSS_API void WheelSettings_SetRadius(WheelSettings* settings, float value);
MOSS_API float WheelSettings_GetWidth(const WheelSettings* settings);
MOSS_API void WheelSettings_SetWidth(WheelSettings* settings, float value);
MOSS_API bool WheelSettings_GetEnableSuspensionForcePoint(const WheelSettings* settings);
MOSS_API void WheelSettings_SetEnableSuspensionForcePoint(WheelSettings* settings, bool value);

MOSS_API Wheel* Wheel_Create(const WheelSettings* settings);
MOSS_API void Wheel_Destroy(Wheel* wheel);
MOSS_API const WheelSettings* Wheel_GetSettings(const Wheel* wheel);
MOSS_API float Wheel_GetAngularVelocity(const Wheel* wheel);
MOSS_API void Wheel_SetAngularVelocity(Wheel* wheel, float value);
MOSS_API float Wheel_GetRotationAngle(const Wheel* wheel);
MOSS_API void Wheel_SetRotationAngle(Wheel* wheel, float value);
MOSS_API float Wheel_GetSteerAngle(const Wheel* wheel);
MOSS_API void Wheel_SetSteerAngle(Wheel* wheel, float value);
MOSS_API bool Wheel_HasContact(const Wheel* wheel);
MOSS_API BodyID Wheel_GetContactBodyID(const Wheel* wheel);
MOSS_API SubShapeID Wheel_GetContactSubShapeID(const Wheel* wheel);
MOSS_API void Wheel_GetContactPosition(const Wheel* wheel, RVec3* result);
MOSS_API void Wheel_GetContactPointVelocity(const Wheel* wheel, Vec3* result);
MOSS_API void Wheel_GetContactNormal(const Wheel* wheel, Vec3* result);
MOSS_API void Wheel_GetContactLongitudinal(const Wheel* wheel, Vec3* result);
MOSS_API void Wheel_GetContactLateral(const Wheel* wheel, Vec3* result);
MOSS_API float Wheel_GetSuspensionLength(const Wheel* wheel);
MOSS_API float Wheel_GetSuspensionLambda(const Wheel* wheel);
MOSS_API float Wheel_GetLongitudinalLambda(const Wheel* wheel);
MOSS_API float Wheel_GetLateralLambda(const Wheel* wheel);
MOSS_API bool Wheel_HasHitHardPoint(const Wheel* wheel);

/* VehicleAntiRollBar */
MOSS_API void VehicleAntiRollBar_Init(VehicleAntiRollBar* antiRollBar);

/* VehicleEngine */
MOSS_API void VehicleEngineSettings_Init(VehicleEngineSettings* settings);

/* VehicleDifferentialSettings */
MOSS_API void VehicleDifferentialSettings_Init(VehicleDifferentialSettings* settings);

/* VehicleTransmission */
MOSS_API VehicleTransmissionSettings* VehicleTransmissionSettings_Create(void);
MOSS_API void VehicleTransmissionSettings_Destroy(VehicleTransmissionSettings* settings);

MOSS_API TransmissionMode VehicleTransmissionSettings_GetMode(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetMode(VehicleTransmissionSettings* settings, TransmissionMode value);

MOSS_API uint32_t VehicleTransmissionSettings_GetGearRatioCount(const VehicleTransmissionSettings* settings);
MOSS_API float VehicleTransmissionSettings_GetGearRatio(const VehicleTransmissionSettings* settings, uint32_t index);
MOSS_API void VehicleTransmissionSettings_SetGearRatio(VehicleTransmissionSettings* settings, uint32_t index, float value);
MOSS_API const float* VehicleTransmissionSettings_GetGearRatios(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetGearRatios(VehicleTransmissionSettings* settings, const float* values, uint32_t count);

MOSS_API uint32_t VehicleTransmissionSettings_GetReverseGearRatioCount(const VehicleTransmissionSettings* settings);
MOSS_API float VehicleTransmissionSettings_GetReverseGearRatio(const VehicleTransmissionSettings* settings, uint32_t index);
MOSS_API void VehicleTransmissionSettings_SetReverseGearRatio(VehicleTransmissionSettings* settings, uint32_t index, float value);
MOSS_API const float* VehicleTransmissionSettings_GetReverseGearRatios(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetReverseGearRatios(VehicleTransmissionSettings* settings, const float* values, uint32_t count);

MOSS_API float VehicleTransmissionSettings_GetSwitchTime(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetSwitchTime(VehicleTransmissionSettings* settings, float value);
MOSS_API float VehicleTransmissionSettings_GetClutchReleaseTime(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetClutchReleaseTime(VehicleTransmissionSettings* settings, float value);
MOSS_API float VehicleTransmissionSettings_GetSwitchLatency(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetSwitchLatency(VehicleTransmissionSettings* settings, float value);
MOSS_API float VehicleTransmissionSettings_GetShiftUpRPM(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetShiftUpRPM(VehicleTransmissionSettings* settings, float value);
MOSS_API float VehicleTransmissionSettings_GetShiftDownRPM(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetShiftDownRPM(VehicleTransmissionSettings* settings, float value);
MOSS_API float VehicleTransmissionSettings_GetClutchStrength(const VehicleTransmissionSettings* settings);
MOSS_API void VehicleTransmissionSettings_SetClutchStrength(VehicleTransmissionSettings* settings, float value);

/* VehicleCollisionTester */
MOSS_API void VehicleCollisionTester_Destroy(VehicleCollisionTester* tester);
MOSS_API ObjectLayer VehicleCollisionTester_GetObjectLayer(const VehicleCollisionTester* tester);
MOSS_API void VehicleCollisionTester_SetObjectLayer(VehicleCollisionTester* tester, ObjectLayer value);

MOSS_API VehicleCollisionTesterRay* VehicleCollisionTesterRay_Create(ObjectLayer layer, const Vec3* up, float maxSlopeAngle);
MOSS_API VehicleCollisionTesterCastSphere* VehicleCollisionTesterCastSphere_Create(ObjectLayer layer, float radius, const Vec3* up, float maxSlopeAngle);
MOSS_API VehicleCollisionTesterCastCylinder* VehicleCollisionTesterCastCylinder_Create(ObjectLayer layer, float convexRadiusFraction);

/* VehicleControllerSettings/VehicleController */
MOSS_API void VehicleControllerSettings_Destroy(VehicleControllerSettings* settings);
MOSS_API const VehicleConstraint* VehicleController_GetConstraint(VehicleController* controller);

/* ---- WheelSettingsWV - WheelWV - WheeledVehicleController ---- */

MOSS_API WheelSettingsWV* WheelSettingsWV_Create(void);
MOSS_API float WheelSettingsWV_GetInertia(const WheelSettingsWV* settings);
MOSS_API void WheelSettingsWV_SetInertia(WheelSettingsWV* settings, float value);
MOSS_API float WheelSettingsWV_GetAngularDamping(const WheelSettingsWV* settings);
MOSS_API void WheelSettingsWV_SetAngularDamping(WheelSettingsWV* settings, float value);
MOSS_API float WheelSettingsWV_GetMaxSteerAngle(const WheelSettingsWV* settings);
MOSS_API void WheelSettingsWV_SetMaxSteerAngle(WheelSettingsWV* settings, float value);
//MOSS_API LinearCurve* WheelSettingsWV_GetLongitudinalFriction(const WheelSettingsWV* settings);
//MOSS_API void WheelSettingsWV_SetLongitudinalFriction(WheelSettingsWV* settings, const LinearCurve* value);
//MOSS_API LinearCurve* WheelSettingsWV_GetLateralFriction(const WheelSettingsWV* settings);
//MOSS_API void WheelSettingsWV_SetLateralFriction(WheelSettingsWV* settings, const LinearCurve* value);
MOSS_API float WheelSettingsWV_GetMaxBrakeTorque(const WheelSettingsWV* settings);
MOSS_API void WheelSettingsWV_SetMaxBrakeTorque(WheelSettingsWV* settings, float value);
MOSS_API float WheelSettingsWV_GetMaxHandBrakeTorque(const WheelSettingsWV* settings);
MOSS_API void WheelSettingsWV_SetMaxHandBrakeTorque(WheelSettingsWV* settings, float value);

MOSS_API WheelWV* WheelWV_Create(const WheelSettingsWV* settings);
MOSS_API const WheelSettingsWV* WheelWV_GetSettings(const WheelWV* wheel);
MOSS_API void WheelWV_ApplyTorque(WheelWV* wheel, float torque, float deltaTime);

MOSS_API WheeledVehicleControllerSettings* WheeledVehicleControllerSettings_Create(void);

MOSS_API void WheeledVehicleControllerSettings_GetEngine(const WheeledVehicleControllerSettings* settings, VehicleEngineSettings* result);
MOSS_API void WheeledVehicleControllerSettings_SetEngine(WheeledVehicleControllerSettings* settings, const VehicleEngineSettings* value);
MOSS_API const VehicleTransmissionSettings* WheeledVehicleControllerSettings_GetTransmission(const WheeledVehicleControllerSettings* settings);
MOSS_API void WheeledVehicleControllerSettings_SetTransmission(WheeledVehicleControllerSettings* settings, const VehicleTransmissionSettings* value);

MOSS_API uint32_t WheeledVehicleControllerSettings_GetDifferentialsCount(const WheeledVehicleControllerSettings* settings);
MOSS_API void WheeledVehicleControllerSettings_SetDifferentialsCount(WheeledVehicleControllerSettings* settings, uint32_t count);
MOSS_API void WheeledVehicleControllerSettings_GetDifferential(const WheeledVehicleControllerSettings* settings, uint32_t index, VehicleDifferentialSettings* result);
MOSS_API void WheeledVehicleControllerSettings_SetDifferential(WheeledVehicleControllerSettings* settings, uint32_t index, const VehicleDifferentialSettings* value);
MOSS_API void WheeledVehicleControllerSettings_SetDifferentials(WheeledVehicleControllerSettings* settings, const VehicleDifferentialSettings* values, uint32_t count);


MOSS_API float WheeledVehicleControllerSettings_GetDifferentialLimitedSlipRatio(const WheeledVehicleControllerSettings* settings);
MOSS_API void WheeledVehicleControllerSettings_SetDifferentialLimitedSlipRatio(WheeledVehicleControllerSettings* settings, float value);

MOSS_API void WheeledVehicleController_SetDriverInput(WheeledVehicleController* controller, float forward, float right, float brake, float handBrake);
MOSS_API void WheeledVehicleController_SetForwardInput(WheeledVehicleController* controller, float forward);
MOSS_API float WheeledVehicleController_GetForwardInput(const WheeledVehicleController* controller);
MOSS_API void WheeledVehicleController_SetRightInput(WheeledVehicleController* controller, float rightRatio);
MOSS_API float WheeledVehicleController_GetRightInput(const WheeledVehicleController* controller);
MOSS_API void WheeledVehicleController_SetBrakeInput(WheeledVehicleController* controller, float brakeInput);
MOSS_API float WheeledVehicleController_GetBrakeInput(const WheeledVehicleController* controller);
MOSS_API void WheeledVehicleController_SetHandBrakeInput(WheeledVehicleController* controller, float handBrakeInput);
MOSS_API float WheeledVehicleController_GetHandBrakeInput(const WheeledVehicleController* controller);
MOSS_API float WheeledVehicleController_GetWheelSpeedAtClutch(const WheeledVehicleController* controller);

/* WheelSettingsTV - WheelTV - TrackedVehicleController */
/* TODO: Add VehicleTrack and VehicleTrackSettings */
MOSS_API WheelSettingsTV* WheelSettingsTV_Create(void);
MOSS_API float WheelSettingsTV_GetLongitudinalFriction(const WheelSettingsTV* settings);
MOSS_API void WheelSettingsTV_SetLongitudinalFriction(WheelSettingsTV* settings, float value);
MOSS_API float WheelSettingsTV_GetLateralFriction(const WheelSettingsTV* settings);
MOSS_API void WheelSettingsTV_SetLateralFriction(WheelSettingsTV* settings, float value);

MOSS_API WheelTV* WheelTV_Create(const WheelSettingsTV* settings);
MOSS_API const WheelSettingsTV* WheelTV_GetSettings(const WheelTV* wheel);

MOSS_API TrackedVehicleControllerSettings* TrackedVehicleControllerSettings_Create(void);

MOSS_API void TrackedVehicleControllerSettings_GetEngine(const TrackedVehicleControllerSettings* settings, VehicleEngineSettings* result);
MOSS_API void TrackedVehicleControllerSettings_SetEngine(TrackedVehicleControllerSettings* settings, const VehicleEngineSettings* value);
MOSS_API const VehicleTransmissionSettings* TrackedVehicleControllerSettings_GetTransmission(const TrackedVehicleControllerSettings* settings);
MOSS_API void TrackedVehicleControllerSettings_SetTransmission(TrackedVehicleControllerSettings* settings, const VehicleTransmissionSettings* value);

MOSS_API void TrackedVehicleController_SetDriverInput(TrackedVehicleController* controller, float forward, float leftRatio, float rightRatio, float brake);
MOSS_API float TrackedVehicleController_GetForwardInput(const TrackedVehicleController* controller);
MOSS_API void TrackedVehicleController_SetForwardInput(TrackedVehicleController* controller, float value);
MOSS_API float TrackedVehicleController_GetLeftRatio(const TrackedVehicleController* controller);
MOSS_API void TrackedVehicleController_SetLeftRatio(TrackedVehicleController* controller, float value);
MOSS_API float TrackedVehicleController_GetRightRatio(const TrackedVehicleController* controller);
MOSS_API void TrackedVehicleController_SetRightRatio(TrackedVehicleController* controller, float value);
MOSS_API float TrackedVehicleController_GetBrakeInput(const TrackedVehicleController* controller);
MOSS_API void TrackedVehicleController_SetBrakeInput(TrackedVehicleController* controller, float value);

/* MotorcycleController */
MOSS_API MotorcycleControllerSettings* MotorcycleControllerSettings_Create(void);
MOSS_API float MotorcycleControllerSettings_GetMaxLeanAngle(const MotorcycleControllerSettings* settings);
MOSS_API void MotorcycleControllerSettings_SetMaxLeanAngle(MotorcycleControllerSettings* settings, float value);
MOSS_API float MotorcycleControllerSettings_GetLeanSpringConstant(const MotorcycleControllerSettings* settings);
MOSS_API void MotorcycleControllerSettings_SetLeanSpringConstant(MotorcycleControllerSettings* settings, float value);
MOSS_API float MotorcycleControllerSettings_GetLeanSpringDamping(const MotorcycleControllerSettings* settings);
MOSS_API void MotorcycleControllerSettings_SetLeanSpringDamping(MotorcycleControllerSettings* settings, float value);
MOSS_API float MotorcycleControllerSettings_GetLeanSpringIntegrationCoefficient(const MotorcycleControllerSettings* settings);
MOSS_API void MotorcycleControllerSettings_SetLeanSpringIntegrationCoefficient(MotorcycleControllerSettings* settings, float value);
MOSS_API float MotorcycleControllerSettings_GetLeanSpringIntegrationCoefficientDecay(const MotorcycleControllerSettings* settings);
MOSS_API void MotorcycleControllerSettings_SetLeanSpringIntegrationCoefficientDecay(MotorcycleControllerSettings* settings, float value);
MOSS_API float MotorcycleControllerSettings_GetLeanSmoothingFactor(const MotorcycleControllerSettings* settings);
MOSS_API void MotorcycleControllerSettings_SetLeanSmoothingFactor(MotorcycleControllerSettings* settings, float value);

MOSS_API float MotorcycleController_GetWheelBase(const MotorcycleController* controller);
MOSS_API bool MotorcycleController_IsLeanControllerEnabled(const MotorcycleController* controller);
MOSS_API void MotorcycleController_EnableLeanController(MotorcycleController* controller, bool value);
MOSS_API bool MotorcycleController_IsLeanSteeringLimitEnabled(const MotorcycleController* controller);
MOSS_API void MotorcycleController_EnableLeanSteeringLimit(MotorcycleController* controller, bool value);
MOSS_API float MotorcycleController_GetLeanSpringConstant(const MotorcycleController* controller);
MOSS_API void MotorcycleController_SetLeanSpringConstant(MotorcycleController* controller, float value);
MOSS_API float MotorcycleController_GetLeanSpringDamping(const MotorcycleController* controller);
MOSS_API void MotorcycleController_SetLeanSpringDamping(MotorcycleController* controller, float value);
MOSS_API float MotorcycleController_GetLeanSpringIntegrationCoefficient(const MotorcycleController* controller);
MOSS_API void MotorcycleController_SetLeanSpringIntegrationCoefficient(MotorcycleController* controller, float value);
MOSS_API float MotorcycleController_GetLeanSpringIntegrationCoefficientDecay(const MotorcycleController* controller);
MOSS_API void MotorcycleController_SetLeanSpringIntegrationCoefficientDecay(MotorcycleController* controller, float value);
MOSS_API float MotorcycleController_GetLeanSmoothingFactor(const MotorcycleController* controller);
MOSS_API void MotorcycleController_SetLeanSmoothingFactor(MotorcycleController* controller, float value);

#ifdef __cplusplus
}
#endif


#endif // MOSS_PHYSICS_H



