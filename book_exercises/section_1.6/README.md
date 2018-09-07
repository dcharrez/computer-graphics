# 1.6 Ejercicios

## 1.6.1 

### Sistema de NDC de -1 a +1

```c
inp_to_ndc( float dcx, float dcy ) {
	ndcx = dcx / ndhm1;
	ndcy = dcy / ndvm1;
}

ndc_to_user( float ndcx, float ndcy ) {
	x = ( ndcx * (1 - (-1)) ) / - (-1);
	y = ( ndcy * (1 - (-1)) ) / - (-1);
}

user_to_ndc( float x, float y ) {
	ndcx = (x - (-1)) / (1 - (-1));
	ndcy = (y - (-1)) / (1 - (-1));
}

ndc_to_dc( float ndcx, float ndcy ) {
	dcx = round(ndcx * ndhm1);
	dcy = round(ndcy * ndvm1);
}
```

## 1.6.2

### Sistema de NDC de 0 a 100

```c
inp_to_ndc( float dcx, float dcy ) {
	ndcx = dcx / ndhm100;
	ndcy = dcy / ndvm1;
}

ndc_to_user( float ndcx, float ndcy ) {
	x = ( ndcx * (100 - (0)) ) / - (0);
	y = ( ndcy * (100 - (0)) ) / - (0);
}

user_to_ndc( float x, float y ) {
	ndcx = (x - (0)) / (100 - (0));
	ndcy = (y - (0)) / (100 - (0));
}

ndc_to_dc( float ndcx, float ndcy ) {
	dcx = round(ndcx * ndhm1);
	dcy = round(ndcy * ndvm1);
}
```