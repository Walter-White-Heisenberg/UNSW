#include<stdio.h>
#include<math.h>

double area(double radius);
double circumference(double radius);
double diameter(double radius);

int main(void)
{double radius;
    printf("Enter circle radius: ");
    scanf("%lf", &radius);
    printf("Area          = %lf\n", area(radius));
    printf("Circumference = %lf\n", circumference(radius));
    printf("Diameter      = %lf\n", diameter(radius));

    return 0;
}


double area(double radius) {

    return radius*radius*M_PI;
}


double circumference(double radius) {

    return M_PI*2*radius; 
}


double diameter(double radius) {

    return 2*radius;
}


