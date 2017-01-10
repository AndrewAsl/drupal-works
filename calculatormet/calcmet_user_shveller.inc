<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/*
 * Шапка
 */
function set_shveller_page(){
    $output = '';
    $output .= render(drupal_get_form('calcmet_undercat_form'));
    $output .= render(drupal_get_form('calcmet_shveller_u_form'));
    $output .= render(drupal_get_form('shveller_spec_form'));
    //$output .= '</div>';
    return $output;
}
function calcmet_undercat_form($form, &$form_state){
    $form['cat'] = array(
        '#title' => t('Категория проката'),
        '#type' => 'select',
        '#options' => calcmet_get_undercategory_title('calcmetundercat'),
        '#default_value' => 10,
        //'#size' => 10,
        '#description' => t('Выберите тип стального проката'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shveller_change_cat',
//        ),
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>'  
    );
    $form_state['rebuild'] = TRUE;
    $cucid = $form_state['values']['cat'];
    return $form;
}

/*
    Раздел по квадрату
 */
function calcmet_shveller_u_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shveller'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shveller']['shvellernames'] = array(
        '#title' => t('Название'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetshveller', 10),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shveller_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shveller']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shveller_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shveller']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['shveller']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['shveller']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shvellsukl.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shveller']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shveller-info">'
        . '<strong>Высота, мм:</strong> <span id="height">50</span><br>'
        . '<strong>Ширина полки, мм:</strong> <span id="width">32</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">4.4</span><br>'
        . '<strong>Толщина полки, мм:</strong> <span id="thickpolka">7.0</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">6.16</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">4.84</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8240-97 "Швеллеры стальные горячекатаные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 27.02.2002 № 10, с учетом изменения №1'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shveller']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshveller.js',
    );
    $form['#action'] = url('/services/calcmet/shveller');
    $form_state['rebuild'] = TRUE;
    return $form;
}

function calcmet_shveller_p_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shveller'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shveller']['shvellernames'] = array(
        '#title' => t('Название'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetshveller', 11),
        '#default_value' => 19,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shveller_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shveller']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shveller_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shveller']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['shveller']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['shveller']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shvellspol.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shveller']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shveller-info">'
        . '<strong>Высота, мм:</strong> <span id="height">50</span><br>'
        . '<strong>Ширина полки, мм:</strong> <span id="width">32</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">4.4</span><br>'
        . '<strong>Толщина полки, мм:</strong> <span id="thickpolka">7.0</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">6.16</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">4.84</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8240-97 "Швеллеры стальные горячекатаные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 27.02.2002 № 10, с учетом изменения №1'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shveller']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshveller.js',
    );
    $form['#action'] = url('/services/calcmet/shveller');
    $form_state['rebuild'] = TRUE;
    return $form;
}

function calcmet_shveller_e_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shveller'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shveller']['shvellernames'] = array(
        '#title' => t('Название'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetshveller', 12),
        '#default_value' => 37,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shveller_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shveller']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shveller_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shveller']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['shveller']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['shveller']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shvellspol.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shveller']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shveller-info">'
        . '<strong>Высота, мм:</strong> <span id="height">50</span><br>'
        . '<strong>Ширина полки, мм:</strong> <span id="width">32</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">4.2</span><br>'
        . '<strong>Толщина полки, мм:</strong> <span id="thickpolka">7.0</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">6.1</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">4.79</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8240-97 "Швеллеры стальные горячекатаные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 27.02.2002 № 10, с учетом изменения №1'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shveller']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshveller.js',
    );
    $form['#action'] = url('/services/calcmet/shveller');
    $form_state['rebuild'] = TRUE;
    return $form;
}

function calcmet_shveller_l_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shveller'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shveller']['shvellernames'] = array(
        '#title' => t('Название'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetshveller', 13),
        '#default_value' => 53,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shveller_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shveller']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shveller_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shveller']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['shveller']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['shveller']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shvellspol.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shveller']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shveller-info">'
        . '<strong>Высота, мм:</strong> <span id="height">120</span><br>'
        . '<strong>Ширина полки, мм:</strong> <span id="width">30</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">3.0</span><br>'
        . '<strong>Толщина полки, мм:</strong> <span id="thickpolka">4.8</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">6.39</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">5.02</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8240-97 "Швеллеры стальные горячекатаные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 27.02.2002 № 10, с учетом изменения №1'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shveller']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshveller.js',
    );
    $form['#action'] = url('/services/calcmet/shveller');
    $form_state['rebuild'] = TRUE;
    return $form;
}

function calcmet_shveller_s_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shveller'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shveller']['shvellernames'] = array(
        '#title' => t('Название'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetshveller', 14),
        '#default_value' => 62,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shveller_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shveller']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shveller_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shveller']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['shveller']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['shveller']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shvellspol.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shveller']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shveller-info">'
        . '<strong>Высота, мм:</strong> <span id="height">80</span><br>'
        . '<strong>Ширина полки, мм:</strong> <span id="width">45</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">5.5</span><br>'
        . '<strong>Толщина полки, мм:</strong> <span id="thickpolka">9.0</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">11.8</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">9.26</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8240-97 "Швеллеры стальные горячекатаные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 27.02.2002 № 10, с учетом изменения №1'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shveller']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshveller.js',
    );
    $form['#action'] = url('/services/calcmet/shveller');
    $form_state['rebuild'] = TRUE;
    return $form;
}

function calcmet_shveller_pol1_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shveller'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shveller']['shvellernames2'] = array(
        '#title' => t('Название'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetshvellerravnopoloch', 15),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shveller_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shveller']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shveller_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shveller']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       '#suffix' =>'</div>'
    );
    /*$form['shveller']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );*/
    $form['shveller']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shvellspol1.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shveller']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shveller-info">'
        . '<strong>Высота, мм:</strong> <span id="height">25</span><br>'
        . '<strong>Ширина, мм:</strong> <span id="width">26</span><br>'
        . '<strong>Толщина, мм:</strong> <span id="thickness">2</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">1.36</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">1.07</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8278-83 "Швеллеры стальные гнутые равнополочные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 № 3 с учетом изменения №2'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shveller']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshveller.js',
    );
    $form['#action'] = url('/services/calcmet/shveller');
    $form_state['rebuild'] = TRUE;
    return $form;
}

function calcmet_shveller_pol2_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shveller'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shveller']['shvellernames2'] = array(
        '#title' => t('Название'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetshvellerravnopoloch', 16),
        '#default_value' => 135,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shveller_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shveller']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shveller_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shveller']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       '#suffix' =>'</div>'
    );
    /*$form['shveller']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );*/
    $form['shveller']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shvellspol1.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shveller']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shveller-info">'
        . '<strong>Высота, мм:</strong> <span id="height">25</span><br>'
        . '<strong>Ширина, мм:</strong> <span id="width">26</span><br>'
        . '<strong>Толщина, мм:</strong> <span id="thickness">2</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">1.39</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">1.09</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8278-83 "Швеллеры стальные гнутые равнополочные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 № 3 с учетом изменения №2'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shveller']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshveller.js',
    );
    $form['#action'] = url('/services/calcmet/shveller');
    $form_state['rebuild'] = TRUE;
    return $form;
}



function shveller_spec_form($form, &$form_state){
    $form['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Название</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        . '<th>Площадь окраски, м2</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    return $form;
}

function shveller_change_info(){
    $select = $_POST['option'];
    $basename = $_POST['shvellername'];
    //dsm($select);
    switch ($basename) {
        case 'shvell1':
            $infos = db_select('calcmetshveller', 'shv1')
                ->fields('shv1', array('shvellerheight', 'shvellerpolkawidth', 'shvellerthickness', 'shvellerpolkathickness', 'shvellercsa', 'massonem', 'drawonemetr'))
                ->condition('shv1.shvellerdid', $select)
                ->execute()
                ->fetchAll();
            $height = $infos[0]->shvellerheight;
            $polkaw = $infos[0]->shvellerpolkawidth;
            $thick = $infos[0]->shvellerthickness;
            $polkathick = $infos[0]->shvellerpolkathickness;
            $csatext = $infos[0]->shvellercsa;
            $massonem = $infos[0]->massonem;
            $csa = $infos[0]->drawonemetr;
        break;
        case 'shvell2':
            $infos = db_select('calcmetshvellerravnopoloch', 'shv2')
                ->fields('shv2', array('shvellerheight', 'shvellerpolkawidth', 'shvellerthickness', 'shvcsa', 'massonem', ))
                ->condition('shv2.shvravnpoldid', $select)
                ->execute()
                ->fetchAll();
            $height = $infos[0]->shvellerheight;
            $polkaw = $infos[0]->shvellerpolkawidth;
            $thick = $infos[0]->shvellerthickness;
            $csatext = $infos[0]->shvcsa;
            $massonem = $infos[0]->massonem;
        break;
        
        default:
        break;
    }
    drupal_json_output(array(                       
                'height'=> $height,                       
                'polkaw'=> $polkaw,                       
                'thick'=> $thick,                       
                'polkathick'=> ($polkathick)?$polkathick:'',                                            
                'csatext'=> $csatext,                       
                'csa'=> ($csa)?$csa:'',                       
                'massonem'=> $massonem,                       
                ));       
    drupal_exit();
}

function calcmet_get_undercategory_title($basename){
     $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetundercat':
                if ($entry->ccid == 8){
                    $options[$entry->cucid] = $entry->title;
                }
                break;
            default:
                break;
        }
    }
    return $options;
}

function calcmet_get_options ($basename, $cucid){
    
    $entries = db_select($basename)
            -> fields($basename)
            -> condition("$basename.cucid", $cucid)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetshveller':
                $options[$entry->shvellerdid] = $entry->shvellername;
                break;
            case 'calcmetshvellerravnopoloch':
                $options[$entry->shvravnpoldid] = $entry->shvellername;
                break;
            default:
                break;
        }
    }
    return $options;
}

function shveller_change_options(){
    $select = $_POST['ajaxshvellerchangeoptions'];
    switch ($select) {
            case 10:
                $form = drupal_render(drupal_get_form('calcmet_shveller_u_form'));                
                break;
            case 11:
                $form = drupal_render(drupal_get_form('calcmet_shveller_p_form'));
                break;
            case 12:
                $form = drupal_render(drupal_get_form('calcmet_shveller_e_form'));
                break;
            case 13:
                $form = drupal_render(drupal_get_form('calcmet_shveller_l_form'));
                break;
            case 14:
                $form = drupal_render(drupal_get_form('calcmet_shveller_s_form'));
                break;
            case 15:
                $form = drupal_render(drupal_get_form('calcmet_shveller_pol1_form'));
                break;
            case 16:
                $form = drupal_render(drupal_get_form('calcmet_shveller_pol2_form'));
                break;

            default:
                break;
        }
    drupal_json_output($form);
    //return $form;
    drupal_exit();
}