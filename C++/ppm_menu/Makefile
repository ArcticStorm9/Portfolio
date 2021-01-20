all: ascii_image questions_3 image_file ppm_menu

questions_3: questions_3.o image_menu.o Image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -g -o questions_3 questions_3.o image_menu.o Image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread

ActionData.o: ActionData.cpp ActionData.h NumberGrid.h
	g++ -g -c ActionData.cpp

questions_3.o: questions_3.cpp image_menu.h ActionData.h MenuData.h NumberGrid.h
	g++ -g -c -g questions_3.cpp

image_menu.o: image_menu.cpp PPM.cpp ActionData.cpp MenuData.cpp NumberGrid.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h
	g++ -g -c image_menu.cpp

Image.o: Image.cpp Image.h image_menu.h ActionData.h
	g++ -g -c Image.cpp

ascii_image.o: ascii_image.cpp Image.h image_menu.h ActionData.h MenuData.h NumberGrid.h
	g++ -g -c ascii_image.cpp

ascii_image: ascii_image.o image_menu.o Image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -g -o ascii_image ascii_image.o Image.o image_menu.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread

image_file: image_file.o image_menu.o Image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -g -o image_file image_file.o image_menu.o Image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread

image_file.o: image_file.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h
	g++ -g -c image_file.cpp

PPM.o: PPM.cpp PPM.h Image.h ActionData.h
	g++ -g -c PPM.cpp

MenuData.o: MenuData.cpp MenuData.h
	g++ -g -c MenuData.cpp

ppm_menu.o: ppm_menu.cpp ActionData.h image_menu.h MenuData.h NumberGrid.h
	g++ -g -c ppm_menu.cpp

ppm_menu: ppm_menu.o ActionData.o image_menu.o MenuData.o Image.o PPM.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -g -o ppm_menu ppm_menu.o image_menu.o MenuData.o ActionData.o Image.o PPM.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread

NumberGrid.o: NumberGrid.cpp NumberGrid.h PPM.h ColorTable.h
	g++ -g -c NumberGrid.cpp

ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h ThreadedGrid.h NumberGrid.h
	g++ -g -c ComplexFractal.cpp

JuliaSet.o: JuliaSet.cpp JuliaSet.h ComplexFractal.h ThreadedGrid.h NumberGrid.h
	g++ -g -c JuliaSet.cpp

ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h ThreadedVector.h NumberGrid.h PPM.h
	g++ -g -c ThreadedGrid.cpp -lpthread

ColorTable.o: ColorTable.cpp ColorTable.h
	g++ -g -c ColorTable.cpp

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h ComplexFractal.h ThreadedGrid.h NumberGrid.h
	g++ -g -c MandelbrotSet.cpp

clean:
	rm image_file.o image_menu.o PPM.o Image.o questions_3.o ascii_image.o ActionData.o MenuData.o NumberGrid.o ppm_menu.o image_file ascii_image questions_3 ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
