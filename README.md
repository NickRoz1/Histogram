#Description

This is a small program for building 2D hists and plotting them in the form of heatmap. Hist building code written in C++, plotting code written in Python using matplotlib.

##Result example
Gaussian distribution (mean 0, standard deviation 1). 

20x20 bins and 50x50 bins.

![Alt text](images/Figure_1_20_20.png?raw=true "20x20")
![Alt text](images/Figure_2_50_50.png?raw=true "50x50")

##Options

User can choose to build histogram using:
* Equal width bins
* Custom width bins

##Usage of binary
```bash
./Histogram (mean value) (standart deviation value) (number of samples) (x min) (x max) (y min) (y max) (x axis bin count) (y axis bin count)
#./Histogram 0.0 1.0 100000 -3 3 -3 3 20 20
```

##Usage of Histogram class
```C++
std::vector<size_t> bins_nums;
std::vector<std::pair<float, float>> limits;

bins_nums.push_back(Xbins_num);
bins_nums.push_back(Ybins_num);
limits.push_back(std::pair<float, float>(Xmin, Xmax));
limits.push_back(std::pair<float, float>(Ymin, Ymax));

auto hist = Histogram(bins_nums, limits);

std::vector<float> point;
point.push_back(X);
point.push_back(Y);
hist.fill(point);
```

##Building
```bash
mkdir build
cd build
cmake ..
make
```



