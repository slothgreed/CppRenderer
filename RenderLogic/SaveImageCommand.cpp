#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
namespace KI
{
namespace Logic
{
SaveImageCommand::SaveImageCommand(shared_ptr<SaveImageCommandArgs> args)
	: ICommand(args)
{

}

CommandResult SaveImageCommand::CanExecute()
{
	auto pArgs = static_pointer_cast<SaveImageCommandArgs>(m_pArgs);

	string directoryPath;
	FileUtility::GetDirectoryPath(pArgs->m_outputPath, directoryPath);
	// TODO:
	//if (FileUtility::IsExist(directoryPath) == false) {
	//	return CommandResult::Failed;
	//}

	if (pArgs->m_pRenderTarget == nullptr) {
		return CommandResult::Failed;
	}

	return CommandResult::Success;

}
CommandResult SaveImageCommand::Execute()
{
	auto pArgs = static_pointer_cast<SaveImageCommandArgs>(m_pArgs);
	
	ReadPixelArgs args;
	args.x = 0;
	args.y = 0;
	args.width = pArgs->m_pRenderTarget->GetSize().x;
	args.height = pArgs->m_pRenderTarget->GetSize().y;
	pArgs->m_pRenderTarget->GetPixels(args, RENDER_TEXTURE_TYPE::RENDER_COLOR_TEXTURE);
	int result = stbi_write_bmp(
		pArgs->m_outputPath.data(), 
		args.width, 
		args.height, 
		glEx::ColorFormatSize(args.format),
		args.pixels);

	if (result == 0) {
		return CommandResult::Failed;
	}

	return CommandResult::Success;
}
}
}