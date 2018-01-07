%Occupation
occupation(joe,oral_surgeon).
occupation(sam,patent_laywer).
occupation(bill,trial_laywer).
occupation(cindy,investment_banker).
occupation(joan,civil_laywer).
occupation(len,plastic_surgeon).
occupation(lance,heart_surgeon).
occupation(frank,brain_surgeon).
occupation(charlie,plastic_surgeon).
occupation(lisa,oral_surgeon).
%Address
address(joe,houston).
address(sam,pittsburgh).
address(bill,dallas).
address(cindy,omaha).
address(joan,chicago).
address(len,college_station).
address(lance,los_angeles).
address(frank,dallas).
address(charlie,houston).
address(lisa,san_antonio).
%Salary
salary(joe,50000).
salary(sam,150000).
salary(bill,200000).
salary(cindy,140000).
salary(joan,80000).
salary(len,70000).
salary(lance,650000).
salary(frank,85000).
salary(charlie,120000).
salary(lisa,190000).
%State City realation
stateofCity(houston,texas).
stateofCity(dallas,texas).
stateofCity(college_station,texas).
stateofCity(san_antonio,texas).
stateofCity(pittsburgh,pennsylvania).
stateofCity(omaha, nebraska).
stateofCity(chicago,illinois).
stateofCity(los_angeles,california).
%Generic occupation
occupationCategory(oral_surgeon,surgeon).
occupationCategory(plastic_surgeon,surgeon).
occupationCategory(heart_surgeon,surgeon).
occupationCategory(brain_surgeon,surgeon).
occupationCategory(patent_laywer,laywer).
occupationCategory(trial_laywer,laywer).
occupationCategory(civil_laywer,laywer).
occupationCategory(investment_banker,banker).
%Query
query(X):- occupation(X,Y),occupationCategory(Y,surgeon),
	address(X,Z),stateofCity(Z,texas),salary(X,U), U > 100000.



















