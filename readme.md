What's is the HBPLv1.0 Plus Version Printer Driver 什么是HBPLv1.0 Plus版打印驱动
-----
The Plus version is the deeply rewrite version for hbplv1.0 printer，it just distinguish between the original coffin's hbplv1.0 printer driver。

Plus版是深度重写的hbplv1.0打印驱动,用于区分原始coffin hbplv1.0的打印驱动。

Index
-----
This is the Linux Printer Driver for HBPLv1.0 Printer ,such as Dell 1250c, Dell C1660w, Dell C1760w, Epson AcuLaser C1700, Fuji-Xerox DocuPrint CP105b.

这是HBPLv1.0 打印机语言的Linux打印机驱动，已知使用该打印语言的打印机有 Dell 1250c, Dell C1660w, Dell C1760w, Epson AcuLaser C1700, Fuji-Xerox DocuPrint CP105b 等. 

Which is rewrite deeply from hbplv1 printer driver， add more features between the original one:

这是深度重写的hbplv1打印驱动，与原始驱动对比，添加更多功能特性：

```
1. Could "Wake Up" the printer when it is "sleeping" in idle time.but the print jobs might be ignored by the printer if it is not ready,since the program could not check the printer status beforce sending the job.
   能够唤醒处于睡眠状态的打印机。但如果打印机没有准备好，打印作业仍可能被打印机忽略,这是由于在发送作业前，程序无法检测打印机状态。

2. Add Manual Duplex Mode
   能手动双面打印

3. Draft Printing Model is available.
   可用草稿模式打印

4. Add 'standard','fineness','color cradation' and 'normal' printing quality selection.
   增加‘标准’，‘精细’，‘色阶’和‘一般’打印质量选项。

5. Could output 300dpi,600dpi and 1200dpi resoultion printing images to the printer,but some printer is still fix at 600dpi resoultion printing like CP105B.
   能够输出 300dpi，600dpi和1200dpi分辨率打印图像至打印机，但有些打印机如cp105b仍是固定在600dpi打印输出。

6. Remove the useless options in ppd file.
   从ppd文件中移除一些无效的选项。

7. Add a5 paper size support
   添加a5纸尺寸支持。

8. Create `configure` , `makefile.in` and `makefile` for easy configure,install and uninstall.
   创建`configure`,`makefile.in`和`makefile`以更容易配置、安装和卸载。
```
if you want to install the original driver ,Here are the script files to install the it easily.

如果你想安装原始的驱动，这里有相关的运行文件可以让你轻松地安装它。

[github](https://github.com/macos2/HBPLv1.0-Printer-driver)

[gitee](https://gitee.com/macos2/HBPLv1.0-Printer-driver)

For more detail about the original driver,go to [Dave Coffin's Home Page](http://www.dechifro.org/hbpl)

想了解原始驱动的详情，请到[Dave Coffin's Home Page](http://www.dechifro.org/hbpl)

Build Dependency 编译依赖
-----
Except the build tool like `gcc` with the strandard c library and `make`，It not need the any other development libraries to compile the programs .

除了带有标准C语言库的gcc编译器及make架构工具以外，并不需要其它的依赖库编译程序。

But it need the `psicc` to transform *.icm,so it also need the some packages like `liblcms2-utils` to make it work fine.

但运行期间，它需要`psicc`去转换*.icm文件，需安装类似`liblcms2-utils`的软件包让其工作正常。

At Fedora， `foo2zjs` also need to be installed since it have not been installed at OS installtion default.

在Fedora环境下需安装`foo2zjs`，因为它默认是没有安装在系统上的。

@Debian 10: `sudo apt install gcc make liblcms2-utils`

@Fedora 31:`sudo dnf install gcc make foo2zjs` //liblcms package is depended by foo2zjs package. liblcms被foo2zjs安装包所依赖

Configure 配置
-----
`./configure` to configure the install path,leave blank for default install path `/usr`

`./configure`配置安装路径，留空使用默认路径`/usr`

you can skip this step if you want to use `/usr` for default install path since a configured `makefile` have been created for default install path.

如果你想安装`/usr` ，你可以跳过该步骤，因为配置好默认路径的`makefile`已经创建了。

Build 编译
-----
just `make` or `make all`

Install 安装
-----
`make install` or `sudo make install`.

Add Printer 添加打印机
-----
Use the `system-config-printer` or other cups admin tools to add the printer with the installed *.ppd as normal printer.

使用`system-config-printer`或其他cups配置工具用安装好的*.ppd文件配置打印机。

The installed *.ppd should be found by the admin tools,or your can special/upload the *.ppd files from the `ppd` directory.

一般情况下，cups配置工具都能找到安装的*.ppd文件，如果没有找到，你可通过指定/上传`ppd`目录下相关*.ppd文件配置打印机。

Command Line Usage 命令行方式使用
-----
1.print something to the *.pdf or *.ps format file(like `output.pdf` or `output.ps`).
  把打印的内容输出成*.pdf 或 *.ps 格式的文件。

2.use command `foo2hbpl1-plus-wrapper [options] < [output.pdf|output.ps] >output.hbpl `to transfrom the *.pdf or *.ps file to hbplv1 language page file（`output.hbpl`）
  通过命令`foo2hbpl1-plus-wrapper [options] < [output.pdf|output.ps] >output.hbpl `把*.pdf 或 *.ps 格式的文件转换成hbplv1页面描述性文件（`output.hbpl`）

3.`cat` the hbplv1 language page file(`output.hbpl`) to printer device(like `/dev/usb/lp0`),`cat output.hbpl >/dev/usb/lp0`. 
  把hbplv1页面描述性文件`cat`到打印机设备(如 `/dev/usb/lp0`)，`cat output.hbpl >/dev/usb/lp0`.

CUPS Usage CUPS方式使用
-----
Select the installed printer in Print Dialog,set up the printing properties and then "print".
在打印对话框中选择已安装的打印机，设置好打印的属性然后打印便可。

Uninstall 卸载
-----
`make uninstall` or `sudo make uninstall`.

Knowed Bugs 已知问题
-----
* The printer might not responed after published the print jobs too frequently ,  Replug the printer usb port should be slove the problem.
  打印过于频繁，打印机可能会对打印作业没有相应，重插打印机usb接口应该可解决问题。

* The print direction may be reversed in some graphic softwares like eog , if you care the direction, you can print the thing into a ghostscript file or a pdf file, and then print the ghostscript file or the pdf file with the printer.
  在某些图像软件如eog，打印图像方向可能会反转，如果你对打印方向有要求，可先把打印内容输出至postscript或pdf文件，然后再用打印机打印该postscript或pdf文件。

* The printer is not responed after first time printing @`Debian 10`（CUPS way）,but it work fine @`Fedora 31`,so I recommend using this driver @`Fedora 31`,but you can skip this problem by command line usage at `Debian 10`.
  在`Debian 10`环境下，首次打印后打印机会对后续的打印作业没有响应(CUPS 方式)，但在`Fedora 31`则没有这个问题，所以我建议你在`Fedora 31`上使用这打印驱动，但你也可以通过命令行的使用方式在`Debian 10`上避开这个使用问题。

