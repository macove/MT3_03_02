#include <Novice.h>
#include <imgui.h>
#include "Vector3.h"
#include "GeometryUtility.h"

const char kWindowTitle[] = "学籍番号";

GeometryUtility geometryUtility;


Vector3 operator+ (const Vector3& v1, const Vector3& v2) { return geometryUtility.Add(v1, v2); }
Vector3 operator- (const Vector3& v1, const Vector3& v2) { return geometryUtility.Subtract(v1, v2); }
Vector3 operator* (const Vector3& v,const float s ) { return geometryUtility.Multiply(s, v); }
Matrix4x4 operator* (const Matrix4x4 m1, const Matrix4x4 m2) { return geometryUtility.Multiply(m1, m2); }
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		





		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		Vector3 a{ 0.2f, 1.0f, 0.0f };
		Vector3 b{ 2.4f, 3.1f, 1.2f };
		Vector3 c = a + b;
		Vector3 d = a - b;
		Vector3 e = a * 2.4f;
		Vector3 rotate{ 0.4f, 1.43f, -0.8f };
		
		Matrix4x4 rotateXMatrix = geometryUtility.MakeRotateXMatrix(rotate.x);
		Matrix4x4 rotateYMatrix = geometryUtility.MakeRotateYMatrix(rotate.y);
		Matrix4x4 rotateZMatrix = geometryUtility.MakeRotateZMatrix(rotate.z);
		Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
		///
		/// ↑更新処理ここまで
		///
		ImGui::Begin("Window");
		ImGui::Text("c: %f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d: %f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e: %f, %f, %f", e.x, e.y, e.z);
		ImGui::Text("matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);
		ImGui::End();
		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
