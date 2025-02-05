# applycr
Apply continuous region average when we get randtools opt result.

# Description
We want to predict well on some of the image series prediction,
however we have noised (gaussian distribution from some test) results on each pixels.
So we want to apply continuous region on them and get their averaged values.

# Hypothesis
We make the hypothesis : bitcount-wise vectors with first binary digit on \<a,x\> for x in {0,1}^n each of the output bit description.
So we interpolate {x} with original image entropy, then, pseudo-integrate them.
