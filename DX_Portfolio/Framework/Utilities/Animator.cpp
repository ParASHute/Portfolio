#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT farmeCount, Vector2 startPos, Vector2 endPos, bool bReversed)
	:clipName(clipName), frameCount(frameCount), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();
	
	// ���ϸ��̼��� �׷��� �ִ� �ؽ�ó�� ����
	Vector2 clipSize = endPos - startPos;

	// Ư����쿡�� ���� �Ǵ� �ڵ带 �����ؾ� ��
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// �ؼ� ������ -> UV���� ��ǥ�� �˾Ƴ��� ����
	texelFrameSize.y = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++) {
		keyFrame.x = texelStartPos.x + (texelFrameSize.x * i);
		keyFrame.y = texelStartPos.y;

		keyFarmes.push_back(keyFrame);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	// �ִ� Ŭ������ �𸦼��� �ֱ� ������
	// �̰� ��¥�� �� ������ �����Ҵ�� ģ���� ����Ʈ �ϱ� ������, �ι�° �ִ� �����常 ����
	for (auto clip : animClips) SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	// ���ϸ��̼� ��� �ð��� �÷��� ����Ʈ���� Ŀ����� 
	// ���ϸ��̼� ����
	if (deltaTime >= playRate) {

		// ������� �ƴ϶��
		if (currentClip->bReversed == false) {
			currentFrameIndex++; // ������ �ε��� ���� (�׸� �׸��� �����׸����� ����)

			// �����ӵ� 0index, ���� �������� 0���� �ʱ�ȭ
			if (currentFrameIndex == currentClip->frameCount) currentFrameIndex = 0;

			// ���� ������ �׸��� ������ ������ ��ȣ�� �׸����� ����
			// ó���� 0���� ������ �ϱ� ������ 0���� ���൵ ��
			currentFrame = currentClip->keyFarmes[currentFrameIndex];
		}

		// ����� -> �̶� ©�� �ִ� ������ ������� �ƴҶ��� �����ϱ� ������ ��� ����
		else {
			currentFrameIndex--;

			// ������ �ִ�ġ
			if (currentFrameIndex == -1) currentFrameIndex = currentClip->frameCount - 1;

			currentFrame = currentClip->keyFarmes[currentFrameIndex];
		}
		deltaTime = 0.0f;
	}

	// ������ �ٲ� �ƴϸ� ����
	else deltaTime += Time::Delta();
}

// �ִϸ����Ϳ��� Ŭ�� ��ü�� �Ѱ��ִ� �Լ�
// �ִϸ����Ͱ� ����� Ŭ���� �ִ� ����
void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{	
	// �������� Ŭ���� ������ ������ Ŭ���� ���� ���/*else*/
	if (currentClip != nullptr) 
		if(currentClip->clipName == clipName) return;

	// Ŭ���� ���� �Ѵٸ�
	// �������� ���ϸ��̼ǰ� ���� ������ �ִϸ��̼��� �ٸ� ��� ��ü �ϱ� ����
	if (CheckExist(clipName)) {
		currentClip = animClips.find(clipName)->second;

		// �������� ���ϸ��̼��� ������ �� ��ŸŸ���� �ʱ�ȭ ��Ű�� ���ο� ���ϸ��̼��� ��Ÿ Ÿ���� ��� ��Ű�� �����̴�.
		deltaTime = 0.0f;

		if (currentClip->bReversed == true) 
			currentFrameIndex = currentClip->frameCount - 1;
		

		else currentFrameIndex = 0;
		
		currentFrame = currentClip->keyFarmes[currentFrameIndex];
	}
}
