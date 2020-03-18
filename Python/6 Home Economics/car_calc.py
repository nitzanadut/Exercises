def calc_months(startPriceOld, startPriceNew, savingPerMonth, percentLossByMonth):
    "Calculates in how many months Uncle Moshe can buy his new car"
    months = savings = 0
    car_price = startPriceNew
    moshe_car_price = startPriceOld

    while savings + moshe_car_price < car_price:
        months += 1

        savings += savingPerMonth
        car_price *= (1 - (percentLossByMonth / 100))
        moshe_car_price *= (1 - (percentLossByMonth / 100))

        if months % 2 == 0:
            percentLossByMonth += .5
    
    return (months, savings + moshe_car_price - car_price)

print(calc_months(2000, 8000, 1000, 0.5))