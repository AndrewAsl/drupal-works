<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/*
 * Шапка
 */
function set_shestigrannik_page(){
    $output = '';
    $output .= render(drupal_get_form('calcmet_undercat_form'));
    $output .= render(drupal_get_form('calcmet_shestigrannik_s_form'));
    $output .= render(drupal_get_form('shestigrannik_spec_form'));
    //$output .= '</div>';
    return $output;
}
function calcmet_undercat_form($form, &$form_state){
    $form['cat'] = array(
        '#title' => t('Категория проката'),
        '#type' => 'select',
        '#options' => calcmet_get_undercategory_title('calcmetundercat'),
        '#default_value' => 17,
        //'#size' => 10,
        '#description' => t('Выберите тип проката'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shestigrannik_change_cat',
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
function calcmet_shestigrannik_s_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shestigrannik'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shestigrannik']['shestigranniknames'] = array(
        '#title' => t('Название'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetsteelshestigran'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shestigrannik_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shestigrannik']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shestigrannik_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shestigrannik']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       '#suffix' =>'</div>'
    );
    /*$form['shestigrannik']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );*/
    $form['shestigrannik']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shestigran1.jpg" width=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shestigrannik']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shestigrannik-info">'
        . '<strong>Диаметр вписанного круга (d), мм</strong> <span id="diametr">8</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">0.554</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.435</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 2879-2006 "Прокат сортовой стальной горячекатаный шестигранный. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 30.01.2007 № 4'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shestigrannik']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshestigrannik.js',
    );
    $form['#action'] = url('/services/calcmet/shestigrannik');
    $form_state['rebuild'] = TRUE;
    return $form;
}

function calcmet_shestigrannik_p_form($form, &$form_state){ 
    
    $form = array();
    
    $form['shestigrannik'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['shestigrannik']['shestigranniknames2'] = array(
        '#title' => t('Размер проката (диаметр вписанного круга (а) или размер "под ключ")'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetcalibrshestigran'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите типоразмер'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'shestigrannik_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['shestigrannik']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'shestigrannik_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['shestigrannik']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['shestigrannik']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['shestigrannik']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/shestigran2.jpg" width=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['shestigrannik']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="shestigrannik-info">'
        .'<strong>Диаметр описанной окружности (А), мм</strong> <span id="diametr2">3.4</span><br>'
        . '<strong>Площадь поперечного сечения, мм2:</strong> <span id="csa">7.79</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.061</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8560-78 "Прокат калиброванный шестигранный. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 № 3 с учетом изменения №2'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['shestigrannik']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetshestigrannik.js',
    );
    $form['#action'] = url('/services/calcmet/shestigrannik');
    $form_state['rebuild'] = TRUE;
    return $form;
}


function shestigrannik_spec_form($form, &$form_state){
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

function shestigrannik_change_info(){
    $select = $_POST['option'];
    $basename = $_POST['shestigrannikname'];
    //dsm($select);
    switch ($basename) {
        case 'shesti1':
            $infos = db_select('calcmetsteelshestigran', 'she1')
                ->fields('she1', array('stshdiametr', 'stshcsa', 'stshmassonem', ))
                ->condition('she1.stshdid', $select)
                ->execute()
                ->fetchAll();
            $diametr = $infos[0]->stshdiametr;
            $csatext = $infos[0]->stshcsa;
            $massonem = $infos[0]->stshmassonem;
        break;
        case 'shesti2':
            $infos = db_select('calcmetcalibrshestigran', 'she2')
                ->fields('she2', array('calshdiametr', 'calshvneshdiametr', 'calshcsa', 'stshmassonem', ))
                ->condition('she2.calshdid', $select)
                ->execute()
                ->fetchAll();
            $diametr = $infos[0]->calshdiametr;
            $diametr2 = $infos[0]->calshvneshdiametr;            
            $csatext = $infos[0]->calshcsa;
            $massonem = $infos[0]->stshmassonem;
            $csa = 6*$diametr2*0.5*0.001;
        break;
        
        default:
        break;
    }
    drupal_json_output(array(                       
                'diametr'=> $diametr,                                                                   
                'diametr2'=> $diametr2,                                                                   
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
                if ($entry->ccid == 9){
                    $options[$entry->cucid] = $entry->title;
                }
                break;
            default:
                break;
        }
    }
    return $options;
}

function calcmet_get_options ($basename){
    
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetsteelshestigran':
                $options[$entry->stshdid] = $entry->stshdiametr;
                break;
            case 'calcmetcalibrshestigran':
                $options[$entry->calshdid] = $entry->calshdiametr;
                break;
            default:
                break;
        }
    }
    return $options;
}

function shestigrannik_change_options(){
    $select = $_POST['ajaxshestigrannikchangeoptions'];
    switch ($select) {
            case 17:
                $form = drupal_render(drupal_get_form('calcmet_shestigrannik_s_form'));                
                break;
            case 18:
                $form = drupal_render(drupal_get_form('calcmet_shestigrannik_p_form'));
                break;

            default:
                break;
        }
    drupal_json_output($form);
    //return $form;
    drupal_exit();
}