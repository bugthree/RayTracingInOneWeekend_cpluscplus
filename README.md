# 1. m_RayTracingInOneWeekend 介绍
复现项目RayTracingInOneWeekend，实现光线追踪

# 2. 程序输出ppm图片的方法
- 打开powershell
- `切换到项目debug目录，也就是含RayTracingProject.exe的那个目录`
- 输入 `.\RayTracingProject.exe > image2.ppm`
    - 其中image2.ppm 代表输出的ppm图片的文件名称
    - 第一次使用powershell运行上面代码会出错`Because the file is written to the program output, you'll need to redirect it to an image file. Typically this is done from the command-line by using the > redirection operator,`
    - 解决方法自行查询
- 打开ppm图片
[一个在线浏览ppm图片的地址](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html)
