def ft_count_harvest_recursive():
    harvest = int(input("Days until harvest: "))
    count_days(1, harvest)

def count_days(day, harvest):
    if day > harvest:
        print("Harvest time!")
    else:
        print("Day ", day)
        count_days(day + 1, harvest)

    