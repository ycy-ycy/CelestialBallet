from PIL import Image
import cv2
import os

# 函数：从文件中读取颜色值并生成图像
def generate_image_from_file(inFile, outFile):
    colors = []  # 存储颜色值的列表

    # 读取文件并逐行处理
    with open(inFile, 'r') as file:
        for line in file:
            # 使用正则表达式提取 (r, g, b) 值
            pxs = list(map(eval, line.strip()[:-1].split(";")))
            colors.append(pxs)

    # 动态设置宽度和高度
    height = len(colors)  # 行数
    width = max(len(row) for row in colors) if colors else 0  # 列数，取最长行的长度

    # 创建一个空白图像
    image = Image.new("RGB", (width, height))

    # 填充图像像素
    for y, row in enumerate(colors):
        for x, (r, g, b) in enumerate(row):
            if x < width and y < height:  # 确保不超出图像边界
                image.putpixel((x, y), (r, g, b))

    # 保存生成的图像
    image.save(outFile)

def generate_video(folder, n, fps, output_file):
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    video = None
    for i in range(n):
        print(i,end=" ")
        inFile = folder + "/" + str(i) + ".dat"
        outFile = folder + "/" + str(i) + ".png"
        generate_image_from_file(inFile, outFile)
        if video is None:
            frame = cv2.imread(outFile)
            height, width, layers = frame.shape
            video = cv2.VideoWriter(output_file, fourcc, fps, (width, height))
        frame = cv2.imread(outFile)
        video.write(frame)
        os.remove(outFile)
    video.release()
    cv2.destroyAllWindows()
    
generate_video("build/test",121,30,"build/twomassivestar.avi")