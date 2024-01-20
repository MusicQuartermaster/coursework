import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns

if __name__ == "__main__":
	df = pd.read_csv('diabetes.csv')
	df.hist(bins=136)

	# Create a subplot of 3 x 3
	figure, axes = plt.subplots(3,3,figsize=(15,15))
	# Make sure there is enough padding to allow titles to be seen 
	figure.tight_layout(pad=5.0)
	# Plot a density plot for each variable 
	for idx, col in enumerate(df.columns): 
		ax = plt.subplot(3,3,idx+1)
		ax.yaxis.set_ticklabels([])
		sns.distplot(df.loc[df.Outcome == 0][col], hist=False, 
		axlabel= False, kde_kws={‘linestyle’:’-’,
		‘color’:’black’, ‘label’:”No Diabetes”})
		sns.distplot(df.loc[df.Outcome == 1][col], hist=False, 
		axlabel= False, kde_kws={‘linestyle’:’--’,
		‘color’:’black’, ‘label’:”Diabetes”}) 
		ax.set_title(col)
	# Hide the 9th subplot (bottom right) since the relationship between the 
	# two outcomes themselves is meaningless
	plt.subplot(3,3,9).set_visible(False) 
	# Show the plot
	plt.show()